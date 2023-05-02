#include <unistd.h>

#include "algorithm.h"
#include "chronometry.h"
#include "debug.h"
#include "draw/cursor.h"
#include "tetris_play_device_input_module_keyboard.h"
#include "tetris_play_fps.h"
#include "tetris_play_main_loop.h"
#include "tetris_play_tetromino_generator.h"
#include "tetris_play_update_world.h"

static void init_game_main_loop(tetris_play_manager_t* const out_play_manager)
{
    debug();

    out_play_manager->status = TETRIS_PLAY_STATUS_RUNNING;
}

static void cleanup_game_main_loop(tetris_play_manager_t* const out_play_manager)
{
    debug();

    (void)(out_play_manager);
    wclear();
}

void* mainfunc_game_main_loop(void* arg)
{
    debug();

    tetris_play_manager_t* const play_manager = (tetris_play_manager_t*)arg;
    init_game_main_loop(play_manager);

    game_time_t prev_frame_time = 0.0;

    int frame_cnt = 0;
    game_time_t acc_time = 0.0f;

    while (play_manager->status == TETRIS_PLAY_STATUS_RUNNING) {
        struct timespec start_time;
        get_chrono_time(&start_time);

        ++frame_cnt;
        wdraw_fps(&frame_cnt, &acc_time);

        play_manager->game_delta_time = prev_frame_time * TETRIS_PLAY_GAME_DELTA_TIME_FACTOR;

        update_gameworld(play_manager);

        __snseconds_t sleep_time = max_long(0L, TO_NSEC(TETRIS_PLAY_FRAME_TIME) - get_elapsed_time_nsec(&start_time));
        nanosleep_chrono(sleep_time);

        prev_frame_time = get_elapsed_time_sec(&start_time);
        acc_time += prev_frame_time;
    }

    for (int i = 1; i < TETRIS_PLAY_SUBMODULE_NUM; ++i) {
        int res = pthread_cancel(play_manager->sub_modules[i].thread_id);
        if (res != 0) {
            handle_error_en("pthread_cancel() error", res);
        }
    }

    cleanup_game_main_loop(play_manager);

    return (void*)play_manager->status;
}

void* new_mainfunc_game_main_loop(void* arg)
{
    debug();

    tetris_play_manager_t* const play_manager = (tetris_play_manager_t*)arg;
    init_game_main_loop(play_manager);

    game_time_t prev_frame_time = 0.0f;

    int frame_cnt = 0;
    game_time_t acc_time = 0.0f;

    while (play_manager->status == TETRIS_PLAY_STATUS_RUNNING) {
        struct timespec start_time;
        get_chrono_time(&start_time);

        ++frame_cnt;
        wdraw_fps(&frame_cnt, &acc_time);

        play_manager->game_delta_time = prev_frame_time * TETRIS_PLAY_GAME_DELTA_TIME_FACTOR;
        new_update_gameworld(play_manager);

        if (new_read_device_input_event(&play_manager->input)) {
            tetromino_status_t res = process_keyboard_event(&play_manager->input, &play_manager->tetro_man);
            process_tetromino_try_status(res, play_manager);
        } else {
            __snseconds_t sleep_time = max_long(0L, TO_NSEC(TETRIS_PLAY_FRAME_TIME) - get_elapsed_time_nsec(&start_time));
            nanosleep_chrono(sleep_time);
        }

        prev_frame_time = get_elapsed_time_sec(&start_time);
        acc_time += prev_frame_time;
    }

    for (int i = 1; i < TETRIS_PLAY_SUBMODULE_NUM; ++i) {
        int res = pthread_cancel(play_manager->sub_modules[i].thread_id);
        if (res != 0) {
            handle_error_en("pthread_cancel() error", res);
        }
    }

    cleanup_game_main_loop(play_manager);

    return (void*)play_manager->status;
}