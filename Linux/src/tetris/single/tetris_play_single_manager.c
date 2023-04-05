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
#include "random.h"
#include "signal_macro.h"
#include "tetris/physics/tetris_play_board_frame.h"
#include "tetris/physics/simulate.h"
#include "tetris/scene/tetris_play_scene.h"
#include "tetris/tetris_play_manager.h"
#include "tetris/tetris_play_submodule.h"
#include "tetris/tetromino/block_code_set.h"
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

static void load_ui(void)
{
    debug();

    int res = load_tetris_play_scene(g_s_play_manager.mode, g_s_play_manager.screen_start_pos_x_wprint, g_s_play_manager.screen_start_pos_y_wprint);
    if (res == -1) {
        handle_error("load_tetris_play_scene() error");
    }
}

static void ready_getset_go(void)
{
    debug();

    for (int cur_sec = g_s_play_manager.ready_getset_go_sec; cur_sec >= 0; --cur_sec) {
        const pos_t pos_x_in_wprint = g_s_play_manager.screen_start_pos_x_wprint + 2;
        const pos_t pos_y_in_wprint = TETRIS_PLAY_BOARD_FRAME_START_POS_Y_WPRINT + TETRIS_PLAY_BOARD_FRAME_WIDTH - 2;
        if (cur_sec == 0) {
            wdraw_digital_digit_at_r(G_DIGITAL_DIGIT_EMPTY, (int)pos_x_in_wprint, (int)pos_y_in_wprint);
            break;
        }
        wdraw_digital_digit_at_r(G_DIGITAL_DIGITS[cur_sec], (int)pos_x_in_wprint, (int)pos_y_in_wprint);
        /* Of course, it's not exactly 1 second. */
        sleep(1);
    }
}

static void init_game_main_module(void)
{
    debug();

    init_rng((unsigned int)time(NULL));
    init_game_board(&g_s_play_manager.board);
    init_tetromino_generator();
}

static void* main_func_game_main_module(void* arg)
{
    debug();

    /* Not a good logic yet. There is a possibility of change,
       but first of all, I will write the code sequentially. */
    game_play_manager_module_arg_t* g_s_play_manager = (game_play_manager_module_arg_t*)arg;
    timer_drawer_t* timer_drawer = &g_s_play_manager->timer_drawer;
    game_board_t* board = &g_s_play_manager->board;
    init_game_main_module();
    bool is_game_over = false;
    while (!is_game_over) {
        const block_code_set_t* code_set = G_BLOCK_CODE_SET_DEFAULT;
        tetromino_t tetromino_obj;
        symbol_id_t symbol_id = (int)(rng() % TOTAL_TETROMINO_NUM_OF_KINDS);
        init_a_tetromino(
            &tetromino_obj,
            symbol_id,
            TETRIS_PLAY_TETROMINO_INIT_POS_X,
            TETRIS_PLAY_TETROMINO_INIT_POS_Y,
            TETRIS_PLAY_TETROMINO_INIT_VELOCITY,
            DIR_BOT,
            code_set->codes[get_block_code_fixed(code_set, symbol_id)]);
        // hmm...
        draw_a_tetromino_r(&tetromino_obj);
        /* Uh.. I think.. The concept of speed should be defined like this,
           "Every few frames it goes down by one block." */
        while (true) {
            // draw_over_all();
            // handle_user_input();
            erase_a_tetromino_r(&tetromino_obj);
            tetromino_status_t status = move_a_tetromino(board, &tetromino_obj);
            draw_a_tetromino_r(&tetromino_obj);
            if (status == TETROMINO_STATUS_ONTHEGROUND) {
                petrity_tetromino(board, &tetromino_obj);
                // clear_filled_lines(); --> maybe internally.
                // reflect_them_visually();
                is_game_over = is_at_skyline(&tetromino_obj);
                break;
            }
            /* Not a good way. Either define a constant or use a separate variable.*/
            usleep(16666);
            // usleep(60000);
        }
    }
    set_realtime_timer(&timer_drawer->timer, false);
    wclear();

    return (void*)TETRIS_PLAY_STATUS_GAME_OVER;
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

    game_play_submodule_t game_play_modules[] = {
        {
            .main_func = main_func_game_main_module,
            .main_func_arg = (void*)&g_s_play_manager,
            .is_detached = false,
        },
        {
            .main_func = main_func_game_play_timer,
            .main_func_arg = (void*)&g_s_play_manager.timer_drawer,
            .is_detached = false,
        },
    };
    size_t game_play_module_num = (size_t)(sizeof(game_play_modules) / sizeof(game_play_modules[0]));

    timer_drawer_t* timer_drawer = &g_s_play_manager.timer_drawer;
    realtime_timer_t* timer = &timer_drawer->timer;

    /* Block REALTIME_TIMER_SIG */
    block_signal(timer->timersig);

    for (size_t i = 0; i < game_play_module_num; ++i) {
        run_game_play_module_in_parallel(game_play_modules + i);
    }
    for (size_t i = 0; i < game_play_module_num; ++i) {
        game_play_submodule_t* const module = game_play_modules + i;
        if (module->is_detached) {
            continue;
        }
        if (pthread_join(module->pthread_id, &module->retval) != 0) {
            handle_error("pthread_join() error");
        }
    }
    game_play_submodule_t* const main_module = game_play_modules + 0;
    return (tetris_play_status_t)(long long)main_module->retval;
}

/*
static int selection_after_game_over(void)
{
    debug();

    // not yet implemented.

    return TETRIS_PLAY_CMD_EXIT_GAME;
} */

static tetris_play_cmd_t run_simulation(void)
{
    debug();

    ready_getset_go();

    if (run_game_play_modules_in_parallel() == TETRIS_PLAY_STATUS_ERROR) {
        handle_error("run_game_play_modules_in_parallel() error");
    }

    /* UX after Game Over not implemented yet. */
    return TETRIS_PLAY_CMD_REGAME;
    // return selection_after_game_over();
}

static tetris_play_cmd_t start_game(void)
{
    debug();

    load_ui();

    tetris_play_cmd_t res;
    if ((res = run_simulation()) == TETRIS_PLAY_CMD_ERROR) {
        handle_error("run_simulation() error");
    }
    return res;
}

static tetris_play_cmd_t play_a_new_game(void)
{
    debug();

    tetris_play_cmd_t res;
    if ((res = start_game()) == -1) {
        handle_error("start_simulation() error");
    }
    return res;
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
