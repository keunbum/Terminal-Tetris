#include <assert.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "chronometry.h"
#include "debug.h"
#include "draw/digital_digit.h"
#include "draw/draw_tool.h"
#include "error_handling.h"
#include "signal_macro.h"
#include "tetris/object/board.h"
#include "tetris/scene/tetris_play_scene.h"
#include "tetris/tetris_play_manager.h"
#include "tetris/tetris_play_submodule.h"
#include "tetris/timer/game_play_timer.h"
#include "tetris/timer/timer_drawer.h"
#include "tetris_play_input_reader.h"
#include "tetris_play_main_loop.h"
#include "tetris_play_single_manager.h"
#include "tetris_play_update_world.h"

static void ready_getset_go(const tetris_play_manager_t* play_manager)
{
    debug();

    for (int cur_sec = play_manager->ready_getset_go_sec; cur_sec >= 0; --cur_sec) {
        struct timespec start_time;
        get_chrono_time(&start_time);
        const pos_t pos_wprint = {
            play_manager->pos_wprint.x + 2,
            play_manager->board.pos_wprint.y + play_manager->board.width - 2,
        };
        if (cur_sec == 0) {
            wdraw_digital_digit5_at_r(G_DIGITAL_DIGIT5_EMPTY, (int)pos_wprint.x, (int)pos_wprint.y);
            break;
        }
        wdraw_digital_digit5_at_r(G_DIGITAL_DIGIT5S[cur_sec], (int)pos_wprint.x, (int)pos_wprint.y);
        /* Of course, it's not exactly 1 second. */
        /* However, it is a bit cumbersome to write a realtime timer haha; */
        nanosleep_chrono(TO_NSEC(1) - get_elapsed_time_nsec(&start_time));
    }
}

static tetris_play_status_t run_tetris_play_modules_in_parallel(tetris_play_manager_t* const out_play_manager)
{
    debug();

    realtime_timer_t* timer = &out_play_manager->timer_drawer.timer;

    /* Block REALTIME_TIMER_SIG */
    block_signal(timer->timersig);

    for (size_t i = 0; i < TETRIS_PLAY_SUBMODULE_NUM; ++i) {
        run_tetris_play_module_in_parallel(out_play_manager->sub_modules + i);
    }

    for (size_t i = 0; i < TETRIS_PLAY_SUBMODULE_NUM; ++i) {
        tetris_play_submodule_t* const module = out_play_manager->sub_modules + i;
        join_tetris_play_module_in_parallel(module);
    }

    const tetris_play_submodule_t* main_module = out_play_manager->sub_modules + 0;
    return (tetris_play_status_t)(long long)main_module->retval;
}

/*
static int selection_after_game_over(void)
{
    debug();

    // not yet implemented.

    return TETRIS_PLAY_CMD_EXIT_GAME;
} */

static void init_tetris_play_objects(tetris_play_manager_t* const out_play_manager)
{
    debug();

    init_frame(&out_play_manager->screen_frame,
        TETRIS_PLAY_SINGLE_SCREEN_HEIGHT_WPRINT, TETRIS_PLAY_SINGLE_SCREEN_WIDTH_WPRINT,
        out_play_manager->pos_wprint,
        NULL,
        UNIT_MATRIX_HOR_LINE,
        UNIT_MATRIX_VER_LINE,
        UNIT_MATRIX_CORNER_TOP_LEFT,
        UNIT_MATRIX_CORNER_TOP_RIGHT,
        UNIT_MATRIX_CORNER_BOT_LEFT,
        UNIT_MATRIX_CORNER_BOT_RIGHT);
    init_board(&out_play_manager->board);
    init_tetromino_manager(&out_play_manager->tetro_man, out_play_manager->tetromino_queue_max_size);
    init_terminal(&out_play_manager->terminal);
    init_timer_drawer(&out_play_manager->timer_drawer, REALTIME_TIMER_SIG);
}

static void init_tetris_play_manager(tetris_play_manager_t* const out_play_manager)
{
    debug();

    my_assert(out_play_manager != NULL);

    out_play_manager->status = TETRIS_PLAY_STATUS_RUNNING;
    init_tetris_play_objects(out_play_manager);
    load_tetris_play_scene(out_play_manager);
}

static void cleanup_tetris_play_objects(tetris_play_manager_t* const out_play_manager)
{
    cleanup_terminal(&out_play_manager->terminal);
    cleanup_tetromino_manager_free(&out_play_manager->tetro_man);
    cleanup_board(&out_play_manager->board);
}

static void cleanup_tetris_play_manager(tetris_play_manager_t* const out_play_manager)
{
    my_assert(out_play_manager != NULL);

    cleanup_tetris_play_scene();
    cleanup_tetris_play_objects(out_play_manager);
}

static tetris_play_cmd_t play_a_new_game(tetris_play_manager_t* const out_play_manager)
{
    debug();

    init_tetris_play_manager(out_play_manager);

    ready_getset_go(out_play_manager);

    if (run_tetris_play_modules_in_parallel(out_play_manager) == TETRIS_PLAY_STATUS_ERROR) {
        handle_error("run_tetris_play_modules_in_parallel() error");
    }

    cleanup_tetris_play_manager(out_play_manager);

    /* UX after Game Over not implemented yet. */
    return TETRIS_PLAY_CMD_REGAME;
    // return selection_after_game_over();
}

/* --------------------------------------------------------------------------------------------------------- */

void* run_tetris_play_single_mode(void* arg)
{
    debug();

    my_assert(arg == NULL);
    (void)arg;

    static tetris_play_manager_t s_play_manager = {
        .ready_getset_go_sec = TETRIS_PLAY_TIMEINTERVAL_BEFORESTART_SEC,
        .tetromino_queue_max_size = TETROMINO_MANAGER_QUEUE_MAX_SIZE,
        .pos_wprint = { TETRIS_PLAY_SINGLE_SCREEN_POS_X_WPRINT, TETRIS_PLAY_SINGLE_SCREEN_POS_Y_WPRINT },
        .play_mode = TETRIS_PLAY_MODE_SINGLE,
        .status = TETRIS_PLAY_STATUS_RUNNING,
        .game_delta_time = 0.0,
        .screen_frame = {
            /* Should be inited with init() */
        },
        .board = {
            /* Also should be inited with init() */
            .block_corner_top_left = BLOCK_WPRINT_BLACK_SQUARE_BUTTON,
            .block_corner_top_right = BLOCK_WPRINT_BLACK_SQUARE_BUTTON,
            .block_corner_bot_left = BLOCK_WPRINT_BLACK_SQUARE_BUTTON,
            .block_corner_bot_right = BLOCK_WPRINT_BLACK_SQUARE_BUTTON,
            .block_ver_line = BLOCK_WPRINT_BLACK_SQUARE_BUTTON,
            .block_hor_line = BLOCK_WPRINT_BLACK_SQUARE_BUTTON,
            .block_inner = BLOCK_WPRINT_WHITE_LARGE_SQUARE,
            .block_skyline = BLOCK_WPRINT_SKYLINE,
            .block_sky = BLOCK_WPRINT_NIGHTSKY,

            .pos = { TETRIS_PLAY_BOARD_POS_X, TETRIS_PLAY_BOARD_POS_Y },
            .pos_wprint = { TETRIS_PLAY_BOARD_POS_X_WPRINT, TETRIS_PLAY_BOARD_POS_Y_WPRINT },
            .frame_pos = { BOARD_FRAME_POS_X, BOARD_FRAME_POS_Y },
            .frame_pos_wprint = { BOARD_FRAME_POS_X_WPRINT, BOARD_FRAME_POS_Y_WPRINT },
            .skyline_pos = { TETRIS_PLAY_SKYLINE_POS_X, BOARD_FRAME_POS_Y},

            .height = TETRIS_PLAY_BOARD_HEIGHT,
            .width = TETRIS_PLAY_BOARD_WIDTH,
            .height_wprint = TETRIS_PLAY_BOARD_HEIGHT_WPRINT,
            .width_wprint = TETRIS_PLAY_BOARD_WIDTH_WPRINT,
            .frame_height = BOARD_FRAME_HEIGHT,
            .frame_width = BOARD_FRAME_WIDTH,
            .skyline = TETRIS_PLAY_SKYLINE_POS_X - TETRIS_PLAY_BOARD_POS_X,
        },
        .tetro_man = {
            /* Should be inited with init() */
        },
        .timer_drawer = {
            /* Also should be inited with init() */
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
                .main_func_arg = (void*)&s_play_manager,
                .is_detached = false,
            },
            {
                .main_func = mainfunc_game_play_timer,
                .main_func_arg = (void*)&s_play_manager.timer_drawer,
                .is_detached = false,
            },
            {
                .main_func = mainfunc_input_reader,
                .main_func_arg = (void*)&s_play_manager,
                .is_detached = false,
            },
        },
    };

    while (true) {
        tetris_play_cmd_t res = play_a_new_game(&s_play_manager);
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
