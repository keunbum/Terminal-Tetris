#include <unistd.h>

#include "debug.h"
#include "game_main_loop.h"
#include "random.h"
#include "tetris/physics/simulate.h"
#include "tetris/physics/tetris_play_board_frame.h"
#include "tetris/scene/tetris_play_scene.h"
#include "tetris/tetris_play_fps.h"
#include "tetris/tetris_play_manager.h"
#include "tetris/tetris_play_submodule.h"
#include "tetris/tetromino/block_code_set.h"

// typedef struct {
//     tetromino_t tetromino;
//     bool is_game_running;
//     clock_t prev_frame_time;
// } game_loop_manager_t;

// static game_loop_manager_t g_s_loop_manager;

// static void new_init_game_main_loop(game_play_manager_module_arg_t* const out_play_manager)
// {
//     init_game_board(&out_play_manager->board);
//     init_tetromino_generator();
//     pos_t pos = { TETRIS_PLAY_TETROMINO_INIT_POS_X, TETRIS_PLAY_TETROMINO_INIT_POS_Y };
//     spawn_a_tetromino(
//         &g_s_loop_manager.tetromino,
//         pos,
//         TETRIS_PLAY_TETROMINO_INIT_VELOCITY);
//     // draw_a_tetromino_r(&g_s_loop_manager.tetromino);
// }

// static void update_tetris_world(game_play_manager_module_arg_t* const out_play_manager, double game_delta_time)
// {
//     tetromino_t* const tetromino_ptr = &g_s_loop_manager.tetromino;
//     erase_a_tetromino_r(tetromino_ptr);
//     tetromino_status_t status = new_move_a_tetromino(&out_play_manager->board, tetromino_ptr, game_delta_time);
//     draw_a_tetromino_r(tetromino_ptr);
//     if (status == TETROMINO_STATUS_ONTHEGROUND) {
//         petrity_tetromino(&out_play_manager->board, tetromino_ptr);
//         // clear_filled_lines(); --> maybe internally.
//         // reflect_them_visually();
//         g_s_loop_manager.is_game_running = !is_at_skyline(tetromino_ptr);
//         return;
//     }
// }

// void* new_mainfunc_game_main_loop(void* arg)
// {
//     game_play_manager_module_arg_t* play_manager = (game_play_manager_module_arg_t*)arg;
//     new_init_game_main_loop(play_manager);
//     g_s_loop_manager.is_game_running = true;
//     while (g_s_loop_manager.is_game_running) {
//         // ... Is it wrong to introduce the concept of FPS to a Tetris game?
//     }
//     return NULL;
// }

/* -------------------------------------------------------------------------------------------------------- */

static void init_game_main_loop(game_play_manager_module_arg_t* const out_play_manager)
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
    game_play_manager_module_arg_t* play_manager = (game_play_manager_module_arg_t*)arg;
    timer_drawer_t* timer_drawer = &play_manager->timer_drawer;
    game_board_t* board = &play_manager->board;
    init_game_main_loop(play_manager);
    bool is_game_over = false;
    while (!is_game_over) {
        const block_code_set_t* code_set = G_BLOCK_CODE_SET_DEFAULT;
        tetromino_t tetromino;
        symbol_id_t symbol_id = (int)(rng() % TOTAL_TETROMINO_NUM_OF_KINDS);
        pos_t tetromino_pos = { TETRIS_PLAY_TETROMINO_INIT_POS_X, TETRIS_PLAY_TETROMINO_INIT_POS_Y };
        init_a_tetromino(
            &tetromino,
            symbol_id,
            tetromino_pos,
            TETRIS_PLAY_TETROMINO_INIT_VELOCITY,
            DIR_BOT,
            code_set->codes[get_block_code_fixed(code_set, symbol_id)]);
        /* The concept of speed should be defined like this,
           "Every few frames it goes down by one block." */
        while (true) {
            // draw_over_all();
            // handle_user_input();
            erase_a_tetromino_r(&tetromino);
            tetromino_status_t status = move_a_tetromino(board, &tetromino);
            draw_a_tetromino_r(&tetromino);
            if (status == TETROMINO_STATUS_ONTHEGROUND) {
                petrity_tetromino(board, &tetromino);
                // clear_filled_lines(); --> maybe internally.
                // reflect_them_visually();
                is_game_over = is_at_skyline(&tetromino);
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