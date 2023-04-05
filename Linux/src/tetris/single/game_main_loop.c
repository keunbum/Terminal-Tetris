#include <unistd.h>

#include "debug.h"
#include "game_main_loop.h"
#include "random.h"
#include "tetris/physics/simulate.h"
#include "tetris/physics/tetris_play_board_frame.h"
#include "tetris/scene/tetris_play_scene.h"
#include "tetris/tetris_play_manager.h"
#include "tetris/tetris_play_submodule.h"
#include "tetris/tetromino/block_code_set.h"

static void init_game_main_loop(game_play_manager_module_arg_t* const out_play_manager)
{
    debug();

    init_rng((unsigned int)time(NULL));
    init_game_board(&out_play_manager->board);
    init_tetromino_generator();
}

void* main_func_game_main_loop(void* arg)
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
        // hmm...
        draw_a_tetromino_r(&tetromino);
        /* Uh.. I think.. The concept of speed should be defined like this,
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