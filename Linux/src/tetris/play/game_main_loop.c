#include <stdio.h>
#include <unistd.h>

#include "debug.h"
#include "game_main_loop.h"
#include "random.h"
#include "update.h"
#include "tetris_play_board_frame.h"
#include "tetris/scene/tetris_play_scene.h"
#include "tetris/tetris_play_manager.h"
#include "tetris/tetris_play_submodule.h"
#include "tetris/tetromino/block_code_set.h"
#include "tetris_play_fps.h"
#include "tetromino_generator.h"
#include "tetris/scene/renderer.h"

// typedef struct {
//     tetromino_t tetromino;
//     bool is_game_running;
//     clock_t prev_frame_time;
// } game_loop_manager_t;

// static game_loop_manager_t g_s_loop_manager;

// static void new_init_game_main_loop(tetris_play_manager_t* const out_play_manager)
// {
//     init_game_board(&out_play_manager->board);
//     init_tetromino_generator();
//     new_spawn_tetromino(&g_s_loop_manager.tetromino);
//     g_s_loop_manager.is_game_running = true;
// }

// static void update_tetris_world(tetris_play_manager_t* const out_play_manager, double game_delta_time)
// {
//     tetromino_t* const tetromino = &g_s_loop_manager.tetromino;
//     erase_a_tetromino_r(tetromino);
//     tetromino_status_t status = new_move_a_tetromino(&out_play_manager->board, tetromino, game_delta_time);
//     draw_a_tetromino_r(tetromino);
//     if (status == TETROMINO_STATUS_ONTHEGROUND) {
//         petrity_tetromino(&out_play_manager->board, tetromino);
//         // clear_filled_lines(); --> maybe internally.
//         // reflect_them_visually();
//         if (is_at_skyline(tetromino)) {
//             g_s_loop_manager.is_game_running = false;
//             return;
//         }
//         new_spawn_tetromino(tetromino);
//     }
// }

// static void render_tetris_world(void)
// {
//     fflush(stdout);
// }

// void* new_mainfunc_game_main_loop(void* arg)
// {
//     tetris_play_manager_t* play_manager = (tetris_play_manager_t*)arg;
//     new_init_game_main_loop(play_manager);
//     while (true) {
//         // read_inputs();
//         update_tetris_world(play_manager, TARGET_FRAME_TIME);
//         render_tetris_world();
//         if (!g_s_loop_manager.is_game_running) {
//             break;
//         }
//         usleep(TARGET_FRAME_TIME * 1e6);
//     }
//     return NULL;
// }

/* -------------------------------------------------------------------------------------------------------- */

static void init_game_main_loop(tetris_play_manager_t* const out_play_manager)
{
    debug();

    init_game_board(&out_play_manager->board);
    init_tetromino_generator();
}

static void init_tetromino_for_play(tetromino_t* const out_tetro)
{
    spawn_tetromino(out_tetro);
}

void* mainfunc_game_main_loop(void* arg)
{
    debug();

    /* Not a good logic yet. There is a possibility of change,
       but first of all, I will write the code sequentially. */
    tetris_play_manager_t* play_manager = (tetris_play_manager_t*)arg;
    timer_drawer_t* timer_drawer = &play_manager->timer_drawer;
    game_board_t* board = &play_manager->board;
    init_game_main_loop(play_manager);
    bool is_game_over = false;
    while (!is_game_over) {
        tetromino_t tetromino;
        init_tetromino_for_play(&tetromino);
        /* The concept of speed should be defined like this,
           "Every few frames it goes down by one block." */
        while (true) {
            // handle_user_input();
            erase_a_tetromino_r(&tetromino);
            tetromino_status_t status = move_a_tetromino(board, &tetromino);
            draw_a_tetromino_r(&tetromino);
            fflush(stdout);
            if (status == TETROMINO_STATUS_ONTHEGROUND) {
                petrity_tetromino(board, &tetromino);
                // clear_filled_lines(); --> maybe internally.
                // reflect_them_visually();
                is_game_over = is_at_skyline(&tetromino);
                break;
            }
            /* Not a good way. Either define a constant or use a separate variable.*/
            //usleep(16666);
            usleep(TARGET_FRAME_TIME * 1e6);
        }
    }
    set_realtime_timer(&timer_drawer->timer, false);
    wclear();

    return (void*)TETRIS_PLAY_STATUS_GAME_OVER;
}