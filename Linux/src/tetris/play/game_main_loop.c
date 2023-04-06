#include <unistd.h>

#include "debug.h"
#include "game_main_loop.h"
#include "random.h"
#include "tetris/scene/renderer.h"
#include "tetris/scene/tetris_play_scene.h"
#include "tetris/tetris_play_manager.h"
#include "tetris/tetris_play_submodule.h"
#include "tetris/tetromino/block_code_set.h"
#include "tetris_play_board_frame.h"
#include "tetris_play_fps.h"
#include "tetromino_generator.h"
#include "update.h"

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
//     spawn_tetromino(&g_s_loop_manager.tetromino);
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
//         spawn_tetromino(tetromino);
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

void* mainfunc_game_main_loop(void* arg)
{
    debug();

    /* Not a good logic yet. There is a possibility of change,
       but first of all, I will write the code sequentially. */
    tetris_play_manager_t* play_manager = (tetris_play_manager_t*)arg;
    init_game_main_loop(play_manager);
    bool is_game_over = false;
    while (!is_game_over) {
        tetromino_t tetromino;
        spawn_tetromino(&play_manager->board, &tetromino);
        while (true) {
            // handle_user_input();
            erase_a_tetromino_r(&tetromino);
            tetromino_status_t status = move_a_tetromino(&play_manager->board, &tetromino);
            draw_a_tetromino_r(&tetromino);
            render_out();
            if (status == TETROMINO_STATUS_ONTHEGROUND) {
                petrity_tetromino(&play_manager->board, &tetromino);
                // clear_filled_lines(); --> maybe internally.
                // reflect_them_visually();
                is_game_over = is_at_skyline(&tetromino);
                break;
            }
            usleep(TARGET_FRAME_TIME * 1e6);
        }
    }
    set_realtime_timer(&play_manager->timer_drawer.timer, false);
    wclear();

    return (void*)TETRIS_PLAY_STATUS_GAME_OVER;
}