#include <unistd.h>

#include "algorithm.h"
#include "chronometry.h"
#include "debug.h"
#include "draw/cursor.h"
#include "tetris_play_device_input.h"
#include "tetris_play_fps.h"
#include "tetris_play_main_loop.h"
#include "tetris_play_update_gameplay.h"

static void init_tetris_play_main_loop(tetris_play_manager_t* const out_play_manager)
{
    out_play_manager->status = TETRIS_PLAY_STATUS_RUNNING;
}

static void cleanup_tetris_play_main_loop(tetris_play_manager_t* const out_play_manager)
{
    (void)(out_play_manager);
    wclear();
}

static void wdraw_game_over(void)
{
    static const wchar_t* S_TITLE[] = {
        L" __             __ ",
        L"/ _   /\\  |\\/| |_  ",
        L"\\__) /--\\ |  | |__ ",
        L" __        __  __    ",
        L"/  \\ \\  / |_  |__) | ",
        L"\\__/  \\/  |__ | \\  . "

    };

    wdraw_rows_newline_at_each(6, S_TITLE, 4, 25);
    wdraw_newline();
    sleep(1);
}

void* mainfunc_tetris_play_main_loop(void* arg)
{
    tetris_play_manager_t* const play_manager = (tetris_play_manager_t*)arg;
    int frame_cnt = 0;
    game_time_t prev_frame_time = 0.0f;
    game_time_t acc_time = 0.0f;

    init_tetris_play_main_loop(play_manager);

    while (play_manager->status == TETRIS_PLAY_STATUS_RUNNING) {
        struct timespec start_time;
        get_chrono_time(&start_time);

        frame_cnt += 1;
        wdraw_fps(&frame_cnt, &acc_time);

        play_manager->game_delta_time = prev_frame_time * TETRIS_PLAY_GAME_DELTA_TIME_FACTOR;
        update_gameplay(play_manager);

        if (read_device_input_event(&play_manager->input)) {
            tetromino_in_play_status_t res = process_input_event(&play_manager->input, &play_manager->tetro_man);
            process_tetromino_status(res, play_manager);
        } else {
            __snseconds_t sleep_time = max_long(0L, TO_NSEC(TETRIS_PLAY_FRAME_TIME) - get_elapsed_time_nsec(&start_time));
            nanosleep_chrono(sleep_time);
        }

        prev_frame_time = get_elapsed_time_sec(&start_time);
        acc_time += prev_frame_time;
    }

    wdraw_game_over();

    for (int i = 1; i < TETRIS_PLAY_SUBMODULE_NUM; ++i) {
        int res = pthread_cancel(play_manager->sub_modules[i].thread_id);
        if (res != 0) {
            handle_error_en("pthread_cancel() error", res);
        }
    }

    cleanup_tetris_play_main_loop(play_manager);

    return (void*)play_manager->status;
}
