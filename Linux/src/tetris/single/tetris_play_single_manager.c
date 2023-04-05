#include <assert.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "debug.h"
#include "draw/cursor.h"
#include "draw/digital_digit.h"
#include "error_handling.h"
#include "game_main_loop.h"
#include "signal_macro.h"
#include "tetris/physics/tetris_play_board_frame.h"
#include "tetris/scene/tetris_play_scene.h"
#include "tetris/tetris_play_manager.h"
#include "tetris/tetris_play_submodule.h"
#include "tetris/timer/game_play_timer.h"
#include "tetris_play_single_manager.h"

static game_play_manager_module_arg_t g_s_play_manager = {
    .mode = TETRIS_PLAY_MODE_SINGLE,
    .screen_start_pos_x_wprint = TETRIS_PLAY_SINGLE_SCREEN_START_POS_X_WPRINT,
    .screen_start_pos_y_wprint = TETRIS_PLAY_SINGLE_SCREEN_START_POS_Y_WPRINT,
    .screen_height_wprint = TETRIS_PLAY_SINGLE_SCREEN_HEIGHT_WPRINT,
    .ready_getset_go_sec = TETRIS_PLAY_TIMEINTERVAL_BEFORESTART_SEC,
    .board = {
        .height = TETRIS_PLAY_BOARD_HEIGHT,
        .width = TETRIS_PLAY_BOARD_WIDTH,
        .height_wprint = TETRIS_PLAY_BOARD_HEIGHT_WPRINT,
        .width_wprint = TETRIS_PLAY_BOARD_WIDTH_WPRINT,
    },
    .timer_drawer = {
        .timer = {
            .clockid = REALTIME_TIMER_CLOCK_ID,
            .its = {
                .it_interval = {
                    .tv_sec = GAME_PLAY_TIMER_IT_INTERVAL_SEC,
                    .tv_nsec = GAME_PLAY_TIMER_IT_INTERVAL_NSEC,
                },
                .it_value = {
                    .tv_sec = GAME_PLAY_TIMER_IT_VALUE_SEC,
                    .tv_nsec = GAME_PLAY_TIMER_IT_VALUE_NSEC,
                },
            },
        },
        .draw_module = {
            .pos_x_wprint = TETRIS_PLAY_TIMER_POS_X_WPRINT,
            .pos_y_wprint = TETRIS_PLAY_TIMER_POS_Y_WPRINT,
            .draw_func = draw_game_play_timer_at_with_r,
        },
    },
};

static void ready_getset_go(void)
{
    debug();

    for (int cur_sec = g_s_play_manager.ready_getset_go_sec; cur_sec >= 0; --cur_sec) {
        const pos_t pos_wprint = {
            g_s_play_manager.screen_start_pos_x_wprint + 2,
            TETRIS_PLAY_BOARD_FRAME_START_POS_Y_WPRINT + TETRIS_PLAY_BOARD_FRAME_WIDTH - 2,
        };
        if (cur_sec == 0) {
            wdraw_digital_digit_at_r(G_DIGITAL_DIGIT_EMPTY, (int)pos_wprint.x, (int)pos_wprint.y);
            break;
        }
        wdraw_digital_digit_at_r(G_DIGITAL_DIGITS[cur_sec], (int)pos_wprint.x, (int)pos_wprint.y);
        /* Of course, it's not exactly 1 second. */
        sleep(1);
    }
}

static void run_game_play_module_in_parallel(game_play_submodule_t* const out_game_play_module)
{
    debug();

    pthread_create(&out_game_play_module->pthread_id, NULL, out_game_play_module->main_func, out_game_play_module->main_func_arg);
    if (out_game_play_module->is_detached) {
        pthread_detach(out_game_play_module->pthread_id);
    }
}

static tetris_play_status_t run_game_play_modules_in_parallel(void)
{
    debug();

    static game_play_submodule_t s_modules[] = {
        {
            .main_func = mainfunc_game_main_loop,
            // .main_func = new_mainfunc_game_main_loop,
            .main_func_arg = (void*)&g_s_play_manager,
            .is_detached = false,
        },
        {
            .main_func = mainfunc_game_play_timer,
            .main_func_arg = (void*)&g_s_play_manager.timer_drawer.timer,
            .is_detached = false,
        },
    };
    static size_t s_module_num = (size_t)(sizeof(s_modules) / sizeof(s_modules[0]));

    timer_drawer_t* timer_drawer = &g_s_play_manager.timer_drawer;
    realtime_timer_t* timer = &timer_drawer->timer;

    /* Block REALTIME_TIMER_SIG */
    block_signal(timer->timersig);

    for (size_t i = 0; i < s_module_num; ++i) {
        run_game_play_module_in_parallel(s_modules + i);
    }

    for (size_t i = 0; i < s_module_num; ++i) {
        game_play_submodule_t* const module = s_modules + i;
        if (module->is_detached) {
            continue;
        }
        if (pthread_join(module->pthread_id, &module->retval) != 0) {
            handle_error("pthread_join() error");
        }
    }
    const game_play_submodule_t* main_module = s_modules + 0;
    return (tetris_play_status_t)(long long)main_module->retval;
}

/*
static int selection_after_game_over(void)
{
    debug();

    // not yet implemented.

    return TETRIS_PLAY_CMD_EXIT_GAME;
} */

static tetris_play_cmd_t play_a_new_game(void)
{
    debug();

    if (load_tetris_play_scene(g_s_play_manager.mode, g_s_play_manager.screen_start_pos_x_wprint, g_s_play_manager.screen_start_pos_y_wprint) == -1) {
        handle_error("load_tetris_play_scene() error");
    }

    ready_getset_go();

    if (run_game_play_modules_in_parallel() == TETRIS_PLAY_STATUS_ERROR) {
        handle_error("run_game_play_modules_in_parallel() error");
    }

    /* UX after Game Over not implemented yet. */
    return TETRIS_PLAY_CMD_REGAME;
    // return selection_after_game_over();
}

/* --------------------------------------------------------------------------------------------------------- */

void* run_tetris_play_single_mode(void* arg)
{
    debug();

    (void)arg;

    g_s_play_manager.timer_drawer.timer.timersig = REALTIME_TIMER_SIG;

    while (true) {
        ewprintf("run_tetris_play_single_mode() HI\n");
        tetris_play_cmd_t res = play_a_new_game();
        if (res == TETRIS_PLAY_CMD_EXIT_GAME) {
            break;
        }
        if (res == TETRIS_PLAY_CMD_ERROR) {
            handle_error("run_single_play() error");
        }
        if (res == TETRIS_PLAY_CMD_REGAME) {
            continue;
        }
        my_assert(false);
    }
    return NULL;
}
