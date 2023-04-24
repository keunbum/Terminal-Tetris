#include <unistd.h>

#include "chronometry.h"
#include "debug.h"
#include "draw/cursor.h"
#include "tetris/tetris_play_fps.h"
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
    while (play_manager->status == TETRIS_PLAY_STATUS_RUNNING) {
        struct timespec start_time;
        get_chrono_time(&start_time);

        play_manager->game_delta_time = prev_frame_time * TETRIS_PLAY_GAME_DELTA_TIME_FACTOR;

        update_gameworld(play_manager);

        __snseconds_t sleep_time = max(0, TO_NSEC(TETRIS_PLAY_FRAME_TIME) - get_elapsed_time_nsec(&start_time));
        nanosleep_chrono(sleep_time);

        prev_frame_time = get_elapsed_time_sec(&start_time);
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