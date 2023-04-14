#include <unistd.h>

#include "chronometry.h"
#include "debug.h"
#include "draw/cursor.h"
#include "game_main_loop.h"
#include "tetris/scene/renderer.h"
#include "tetris_play_fps.h"
#include "tetris_play_update.h"
#include "tetromino_generator.h"

static void init_game_main_loop(tetris_play_manager_t* const out_play_manager)
{
    debug();

    init_game_board(&out_play_manager->board);
    init_tetromino_generator();
    out_play_manager->tetromino.id = -1;
    out_play_manager->prev_tetromino.id = -1;
    out_play_manager->status = TETRIS_PLAY_STATUS_RUNNING;
}

void* mainfunc_game_main_loop(void* arg)
{
    debug();

    tetris_play_manager_t* play_manager = (tetris_play_manager_t*)arg;
    game_time_t prev_frame_time = 0.0;

    init_game_main_loop(play_manager);

    while (play_manager->status == TETRIS_PLAY_STATUS_RUNNING) {
        struct timespec start_time;
        get_chrono_time(&start_time);

        play_manager->game_delta_time = prev_frame_time * TETRIS_PLAY_GAME_DELTA_TIME_FACTOR;

        update_gameworld(play_manager);
        render_out(play_manager);

        nanosleep_chrono(TO_NSEC(TETRIS_PLAY_FRAME_TIME) - get_elapsed_time_nsec(&start_time));

        prev_frame_time = get_elapsed_time_sec(&start_time);
    }

    for (int i = 1; i < TETRIS_PLAY_SUBMODULE_NUM; ++i) {
        int res = pthread_cancel(play_manager->sub_modules[i].pthread_id);
        if (res != 0) {
            handle_error_en("pthread_cancel() error", res);
        }
    }

    wclear();
    
    return (void*)play_manager->status;
}