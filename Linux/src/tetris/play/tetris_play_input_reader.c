#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>

#include "debug.h"
#include "pthread_macro.h"
#include "tetris/play/tetris_play_update_world.h"
#include "tetris/tetris_play_manager.h"
#include "tetris_play_input_reader.h"

static tetromino_try_status_t process_input_event(const struct input_event* ev, tetris_play_manager_t* const out_play_manager)
{
    debug();

    board_t* board = &out_play_manager->board;
    tetromino_t* tetro = out_play_manager->tetro_man.tetro_main;
    // tetromino_manager_t* tetro_man = &out_play_manager->tetro_man;
    tetromino_try_status_t ret = TETROMINO_TRY_STATUS_NULL;
    if (ev->type == EV_KEY) {
        if (ev->value == 1) {
            switch (ev->code) {
            case KEY_DOWN:
                ret = try_move_tetromino_byone_r(board, tetro, DIR_BOT);
                break;
            case KEY_LEFT:
                // hhmm.. may be implemented reversed??
                ret = try_move_tetromino_byone_r(board, tetro, DIR_LEFT);
                break;
            case KEY_RIGHT:
                ret = try_move_tetromino_byone_r(board, tetro, DIR_RIGHT);
                break;
            case KEY_UP:
                /* intentional fallthrough */
            case KEY_X:
                ret = try_rotate_tetromino_r(board, tetro, -1);
                break;
            case KEY_SPACE:
                ret = harddrop_tetromino_r(board, tetro);
                break;
            case KEY_Z:
                ret = try_rotate_tetromino_r(board, tetro, +1);
                break;
            case KEY_C:
                /* Not yet implemented */
                // swap_tetromino_hold(tetro_man);
                break;
            case KEY_ESC:
                /* Not a good logic */
                /* A pause is ideal */
                exit_cleanup_game_system(EXIT_SUCCESS);
                break;
            }
        } else if (ev->value == 2) {
            switch (ev->code) {
            case KEY_DOWN:
                try_move_tetromino_byone_r(board, tetro, DIR_BOT);
                break;
            case KEY_LEFT:
                try_move_tetromino_byone_r(board, tetro, DIR_LEFT);
                break;
            case KEY_RIGHT:
                try_move_tetromino_byone_r(board, tetro, DIR_RIGHT);
                break;
            }
        }
    }
    return ret;
}

static void cleanup_input_reader_module(void* arg)
{
    debug();

    my_assert(arg != NULL);

    input_reader_t* const input_reader = (input_reader_t*)arg;
    cleanup_input_reader(input_reader);
}

void* mainfunc_input_reader(void* arg)
{
    debug();

    tetris_play_manager_t* const play_manager = (tetris_play_manager_t*)arg;

    input_reader_t input_reader;
    init_input_reader(&input_reader);
    pthread_cleanup_push(cleanup_input_reader_module, &input_reader);

    while (true) {
        read_input_event(&input_reader);
        // hmm.. locking board looks inappropriate
        lock_board(&play_manager->board);
        tetromino_try_status_t res = process_input_event(&input_reader.event, play_manager);
        process_tetromino_try_status(res, play_manager);
        unlock_board(&play_manager->board);
    }

    return NULL;
}