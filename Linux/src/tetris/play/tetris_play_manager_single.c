#include <assert.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "chronometry.h"
#include "debug.h"
#include "device_input.h"
#include "draw/digital_digit.h"
#include "draw/draw_tool.h"
#include "error_handling.h"
#include "signal_macro.h"
#include "tetris/object/matrix.h"
#include "tetris/scene/tetris_play_scene.h"
#include "tetris/timer/game_play_timer.h"
#include "tetris/timer/tetris_play_timer.h"
#include "tetris_play_main_loop.h"
#include "tetris_play_manager.h"
#include "tetris_play_manager_single.h"
#include "tetris_play_update_gameplay.h"

static void ready_getset_go(const tetris_play_manager_t* play_manager)
{
    for (int cur_sec = play_manager->ready_getset_go_sec; cur_sec >= 0; --cur_sec) {
        struct timespec start_time;
        get_chrono_time(&start_time);
        const pos_int_t digital_digit_pos_wprint = {
            play_manager->screen_pos_wprint.x + 2,
            play_manager->tetro_man.matrix.in_play_pos_wprint.y + 8,
        };
        if (cur_sec == 0) {
            wdraw_digital_digit5_at(G_DIGITAL_DIGIT5_EMPTY, digital_digit_pos_wprint.x, digital_digit_pos_wprint.y);
            break;
        }
        wdraw_digital_digit5_at(G_DIGITAL_DIGIT5S[cur_sec], digital_digit_pos_wprint.x, digital_digit_pos_wprint.y);
        nanosleep_chrono(TO_NSEC(1) - get_elapsed_time_nsec(&start_time));
    }
}

static tetris_play_status_t run_tetris_play_modules_in_parallel(tetris_play_manager_t* const out_play_manager)
{
    realtime_timer_t* timer = &out_play_manager->tetris_play_timer.game_play_timer.realtime_timer;

    /* Block REALTIME_TIMER_SIG */
    block_signal(timer->timersig);

    for (size_t i = 0; i < TETRIS_PLAY_SUBMODULE_NUM; ++i) {
        run_thread_module(out_play_manager->sub_modules + i);
    }

    for (size_t i = 0; i < TETRIS_PLAY_SUBMODULE_NUM; ++i) {
        thread_module_t* const module = out_play_manager->sub_modules + i;
        join_thread_module(module);
    }

    const thread_module_t* main_module = out_play_manager->sub_modules + 0;
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
    init_frame(&out_play_manager->screen_frame,
        TETRIS_PLAY_SINGLE_SCREEN_HEIGHT_WPRINT,
        TETRIS_PLAY_SINGLE_SCREEN_WIDTH_WPRINT,
        out_play_manager->screen_pos_wprint,
        NULL,
        UNIT_MATRIX_HOR_LINE,
        UNIT_MATRIX_VER_LINE,
        UNIT_MATRIX_CORNER_TOP_LEFT,
        UNIT_MATRIX_CORNER_TOP_RIGHT,
        UNIT_MATRIX_CORNER_BOT_LEFT,
        UNIT_MATRIX_CORNER_BOT_RIGHT);
    init_tetromino_manager(&out_play_manager->tetro_man, out_play_manager->tetromino_next_queue_max_size);
    init_terminal(&out_play_manager->terminal);
    init_tetris_play_timer(&out_play_manager->tetris_play_timer, (pos_int_t) { TETRIS_PLAY_TIMER_POS_X_WPRINT, TETRIS_PLAY_TIMER_POS_Y_WPRINT }, REALTIME_TIMER_SIG);
}

static void cleanup_tetris_play_objects(tetris_play_manager_t* const out_play_manager)
{
    cleanup_device_input(&out_play_manager->input);
    cleanup_tetris_play_timer(&out_play_manager->tetris_play_timer);
    cleanup_terminal(&out_play_manager->terminal);
    cleanup_tetromino_manager_free(&out_play_manager->tetro_man);
}

static void init_tetris_play_manager_before_start(tetris_play_manager_t* const out_play_manager)
{
    out_play_manager->status = TETRIS_PLAY_STATUS_RUNNING;
    init_tetris_play_objects(out_play_manager);
    init_tetris_play_scene(out_play_manager);
}

static void init_tetris_play_manager_after_start(tetris_play_manager_t* const out_play_manager)
{
    init_device_input(&out_play_manager->input, DEVICE_INPUT_KEYBOARD, O_RDONLY | O_NONBLOCK);
}

static void cleanup_tetris_play_manager(tetris_play_manager_t* const out_play_manager)
{
    cleanup_tetris_play_scene();
    cleanup_tetris_play_objects(out_play_manager);
}

static tetris_play_cmd_t play_a_new_game(tetris_play_manager_t* const out_play_manager)
{
    init_tetris_play_manager_before_start(out_play_manager);
    ready_getset_go(out_play_manager);
    init_tetris_play_manager_after_start(out_play_manager);

    if (run_tetris_play_modules_in_parallel(out_play_manager) == TETRIS_PLAY_STATUS_ERROR) {
        handle_error("run_tetris_play_modules_in_parallel() error");
    }

    cleanup_tetris_play_manager(out_play_manager);

    /* UX after Game Over not implemented yet. */
    return TETRIS_PLAY_CMD_REGAME;
    // return selection_after_game_over();
}

/* --------------------------------------------------------------------------------------------------------- */

void* run_tetris_play_manager_single(void* arg)
{
    (void)arg;

    static tetris_play_manager_t s_play_manager = {
        .ready_getset_go_sec = TETRIS_PLAY_TIMEINTERVAL_BEFORESTART_SEC,
        .tetromino_next_queue_max_size = TETRIS_PLAY_TETROMINO_MANAGER_QUEUE_MAX_SIZE,
        .screen_pos_wprint = { TETRIS_PLAY_SINGLE_SCREEN_POS_X_WPRINT, TETRIS_PLAY_SINGLE_SCREEN_POS_Y_WPRINT },
        .play_mode = TETRIS_PLAY_MODE_SINGLE,
        .status = TETRIS_PLAY_STATUS_RUNNING,
        .game_delta_time = 0.0,
        .screen_frame = {
            /* Should be inited with init() */
        },
        .tetro_man = {
            /* Also be inited with init() */
            .matrix = {
                /* Also should be inited with init() */
                .block_corner_top_left = MATRIX_WALL_BLOCK_WPRINT,
                .block_corner_top_right = MATRIX_WALL_BLOCK_WPRINT,
                .block_corner_bot_left = MATRIX_WALL_BLOCK_WPRINT,
                .block_corner_bot_right = MATRIX_WALL_BLOCK_WPRINT,
                .block_ver_line = MATRIX_WALL_BLOCK_WPRINT,
                .block_hor_line = MATRIX_WALL_BLOCK_WPRINT,
                .block_in_play = MATRIX_INNTER_BLOCK_WPRINT,
                .block_skyline = MATRIX_WALL_BLOCK_WPRINT,

                .pos = { TETRIS_PLAY_MATRIX_POS_X, TETRIS_PLAY_MATRIX_POS_Y },
                .in_play_pos_wprint = { TETRIS_PLAY_MATRIX_IN_PLAY_POS_X_WPRINT, TETRIS_PLAY_MATRIX_IN_PLAY_POS_Y_WPRINT },
                .frame_pos = { MATRIX_FRAME_POS_X, MATRIX_FRAME_POS_Y },
                .frame_pos_wprint = { MATRIX_FRAME_POS_X_WPRINT, MATRIX_FRAME_POS_Y_WPRINT },
                .skyline_pos = { TETRIS_PLAY_SKYLINE_POS_X, MATRIX_FRAME_POS_Y },

                .height = TETRIS_PLAY_MATRIX_HEIGHT,
                .in_play_height = TETRIS_PLAY_MATRIX_IN_PLAY_HEIGHT,
                .width = TETRIS_PLAY_MATRIX_WIDTH,
                .height_wprint = TETRIS_PLAY_MATRIX_HEIGHT_WPRINT,
                .width_wprint = TETRIS_PLAY_MATRIX_WIDTH_WPRINT,
                .frame_height = MATRIX_FRAME_HEIGHT,
                .frame_width = MATRIX_FRAME_WIDTH,
                .skyline_i = TETRIS_PLAY_SKYLINE_POS_X - TETRIS_PLAY_MATRIX_POS_X,
            },
        },
        .sub_modules = {
            {
                .main_func = mainfunc_tetris_play_main_loop,
                .main_func_arg = (void*)&s_play_manager,
                .is_detached = false,
            },
            {
                .main_func = run_tetris_play_timer,
                .main_func_arg = (void*)&s_play_manager.tetris_play_timer,
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
