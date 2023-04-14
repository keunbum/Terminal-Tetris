#include <assert.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "chronometry.h"
#include "debug.h"
#include "draw/digital_digit.h"
#include "error_handling.h"
#include "signal_macro.h"
#include "tetris/object/board.h"
#include "tetris/scene/tetris_play_scene.h"
#include "tetris/tetris_play_manager.h"
#include "tetris/tetris_play_submodule.h"
#include "tetris/timer/game_play_timer.h"
#include "tetris_play_input_reader.h"
#include "tetris_play_main_loop.h"
#include "tetris_play_single_manager.h"
#include "tetris_play_update_world.h"

static tetris_play_manager_t g_s_play_manager = {
    .play_mode = TETRIS_PLAY_MODE_SINGLE,
    .screen_start_pos_x_wprint = TETRIS_PLAY_SINGLE_SCREEN_POS_X_WPRINT,
    .screen_start_pos_y_wprint = TETRIS_PLAY_SINGLE_SCREEN_POS_Y_WPRINT,
    .screen_height_wprint = TETRIS_PLAY_SINGLE_SCREEN_HEIGHT_WPRINT,
    .ready_getset_go_sec = TETRIS_PLAY_TIMEINTERVAL_BEFORESTART_SEC,
    .game_delta_time = 0.0,
    .screen = {
        .pos = { TETRIS_PLAY_SINGLE_SCREEN_POS_X, TETRIS_PLAY_SINGLE_SCREEN_POS_Y },
        .pos_wprint = { TETRIS_PLAY_SINGLE_SCREEN_POS_X_WPRINT, TETRIS_PLAY_SINGLE_SCREEN_POS_Y_WPRINT },
    },
    .board = {
        .block_corner_top_left = BLOCK_WPRINT_BLACK_SQUARE_BUTTON,
        .block_corner_top_right = BLOCK_WPRINT_BLACK_SQUARE_BUTTON,
        .block_corner_bot_left = BLOCK_WPRINT_BLACK_SQUARE_BUTTON,
        .block_corner_bot_right = BLOCK_WPRINT_BLACK_SQUARE_BUTTON,
        .block_ver_line = BLOCK_WPRINT_BLACK_SQUARE_BUTTON,
        .block_hor_line = BLOCK_WPRINT_BLACK_SQUARE_BUTTON,
        .block_inner = BLOCK_WPRINT_WHITE_LARGE_SQUARE,

        .height = TETRIS_PLAY_BOARD_HEIGHT,
        .width = TETRIS_PLAY_BOARD_WIDTH,
        .height_wprint = TETRIS_PLAY_BOARD_HEIGHT_WPRINT,
        .width_wprint = TETRIS_PLAY_BOARD_WIDTH_WPRINT,
        .frame_height = BOARD_FRAME_HEIGHT,
        .frame_width = BOARD_FRAME_WIDTH,
        .pos = { TETRIS_PLAY_BOARD_POS_X, TETRIS_PLAY_BOARD_POS_Y },
        .pos_wprint = { TETRIS_PLAY_BOARD_POS_X_WPRINT, TETRIS_PLAY_BOARD_POS_Y_WPRINT },
        .frame_pos = { BOARD_FRAME_POS_X, BOARD_FRAME_POS_Y },
        .frame_pos_wprint = { BOARD_FRAME_POS_X_WPRINT, BOARD_FRAME_POS_Y_WPRINT },
    },
    .statistics = {
        .pos = { TETRIS_PLAY_STATISTIC_POS_X, TETRIS_PLAY_STATISTIC_POS_Y },
        .pos_wprint = { TETRIS_PLAY_STATISTIC_POS_X_WPRINT, TETRIS_PLAY_STATISTIC_POS_Y_WPRINT },
        .tetromino_pos_wprint = { TETRIS_PLAY_STATISTIC_TETROMINO_POS_X_WPRINT, TETRIS_PLAY_STATISTIC_TETROMINO_POS_Y_WPRINT },
        .interval_height = TETRIS_PLAY_STATISTIC_INTERVAL_HEIGHT,
    },
    .tetromino = {
        .id = -1,
    },
    .prev_tetromino = {
        .id = -1,
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
    .sub_modules = {
        {
            .main_func = mainfunc_game_main_loop,
            .main_func_arg = (void*)&g_s_play_manager,
            .is_detached = false,
        },
        {
            .main_func = mainfunc_game_play_timer,
            .main_func_arg = (void*)&g_s_play_manager.timer_drawer,
            .is_detached = false,
        },
        {
            .main_func = mainfunc_input_reader,
            .main_func_arg = (void*)&g_s_play_manager,
            .is_detached = false,
        },
    },
};

static void ready_getset_go(void)
{
    debug();

    for (int cur_sec = g_s_play_manager.ready_getset_go_sec; cur_sec >= 0; --cur_sec) {
        struct timespec start_time;
        get_chrono_time(&start_time);

        const pos_t pos_wprint = {
            g_s_play_manager.screen_start_pos_x_wprint + 2,
            BOARD_FRAME_POS_Y_WPRINT + BOARD_FRAME_WIDTH - 2,
        };
        if (cur_sec == 0) {
            wdraw_digital_digit_at_r(G_DIGITAL_DIGIT_EMPTY, (int)pos_wprint.x, (int)pos_wprint.y);
            break;
        }
        wdraw_digital_digit_at_r(G_DIGITAL_DIGITS[cur_sec], (int)pos_wprint.x, (int)pos_wprint.y);
        /* Of course, it's not exactly 1 second. */
        /* However, it is a bit cumbersome to write a timer haha; */
        nanosleep_chrono(TO_NSEC(1) - get_elapsed_time_nsec(&start_time));
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

    timer_drawer_t* timer_drawer = &g_s_play_manager.timer_drawer;
    realtime_timer_t* timer = &timer_drawer->timer;

    /* Block REALTIME_TIMER_SIG */
    block_signal(timer->timersig);

    for (size_t i = 0; i < TETRIS_PLAY_SUBMODULE_NUM; ++i) {
        run_game_play_module_in_parallel(g_s_play_manager.sub_modules + i);
    }

    for (size_t i = 0; i < TETRIS_PLAY_SUBMODULE_NUM; ++i) {
        game_play_submodule_t* const module = g_s_play_manager.sub_modules + i;
        if (module->is_detached) {
            continue;
        }
        if (pthread_join(module->pthread_id, &module->retval) != 0) {
            handle_error("pthread_join() error");
        }
    }

    const game_play_submodule_t* main_module = g_s_play_manager.sub_modules + 0;
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

    // load_tetris_play_scene(g_s_play_manager.play_mode, g_s_play_manager.screen_start_pos_x_wprint, g_s_play_manager.screen_start_pos_y_wprint);
    load_tetris_play_objects(&g_s_play_manager);
    new_load_tetris_play_scene(&g_s_play_manager);

    ready_getset_go();

    if (run_game_play_modules_in_parallel() == TETRIS_PLAY_STATUS_ERROR) {
        handle_error("run_game_play_modules_in_parallel() error");
    }

    cleanup_tetris_play_scene();

    /* UX after Game Over not implemented yet. */
    return TETRIS_PLAY_CMD_REGAME;
    // return selection_after_game_over();
}

static void init_tetris_play_manager(tetris_play_manager_t* const out_play_manager)
{
    out_play_manager->timer_drawer.timer.timersig = REALTIME_TIMER_SIG;
}

/* --------------------------------------------------------------------------------------------------------- */

void* run_tetris_play_single_mode(void* arg)
{
    debug();

    my_assert(arg == NULL);
    (void)arg;

    init_tetris_play_manager(&g_s_play_manager);

    while (true) {
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
