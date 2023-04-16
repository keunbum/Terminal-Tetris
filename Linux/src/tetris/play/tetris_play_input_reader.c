#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>

#include "debug.h"
#include "pthread_macro.h"
#include "tetris/play/tetris_play_update_tetromino_status.h"
#include "tetris/tetris_play_manager.h"
#include "tetris_play_input_reader.h"

static void process_input_event(const struct input_event* ev, tetris_play_manager_t* const out_play_manager)
{
    // if (out_play_manager->status != TETRIS_PLAY_STATUS_RUNNING) {
    //     return;
    // }

    if (ev->type == EV_KEY) {

        if (ev->value == 1) {
            switch (ev->code) {
            case KEY_DOWN:
                try_move_tetromino_byone_r(&out_play_manager->board, &out_play_manager->tetromino, DIR_BOT);
                break;
            case KEY_LEFT:
                try_move_tetromino_byone_r(&out_play_manager->board, &out_play_manager->tetromino, DIR_LEFT);
                break;
            case KEY_RIGHT:
                try_move_tetromino_byone_r(&out_play_manager->board, &out_play_manager->tetromino, DIR_RIGHT);
                break;
            case KEY_UP:
                /* intentional fallthrough */
            case KEY_X:
                try_rotate_tetromino_r(&out_play_manager->board, &out_play_manager->tetromino, 1);
                break;
            case KEY_SPACE:
                harddrop_tetromino_r(&out_play_manager->tetromino);
                break;
            case KEY_Z:
                try_rotate_tetromino_r(&out_play_manager->board, &out_play_manager->tetromino, -1);
                break;
            case KEY_C:
                /* Not yet implemented */
                // keep_tetromino(...);
                break;
            case KEY_ESC:
                /* Not a good logic */
                /* A pause is ideal */
                exit_cleanup_game_system(EXIT_SUCCESS);
                break;
            }
            return;
        }

        if (ev->value == 2) {
            switch (ev->code) {
            case KEY_DOWN:
                try_move_tetromino_byone_r(&out_play_manager->board, &out_play_manager->tetromino, DIR_BOT);
                break;
            case KEY_LEFT:
                try_move_tetromino_byone_r(&out_play_manager->board, &out_play_manager->tetromino, DIR_LEFT);
                break;
            case KEY_RIGHT:
                try_move_tetromino_byone_r(&out_play_manager->board, &out_play_manager->tetromino, DIR_RIGHT);
                break;
            }
            return;
        }
    }
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
    return NULL;
    
    debug();

    tetris_play_manager_t* const play_manager = (tetris_play_manager_t*)arg;

    input_reader_t input_reader;
    init_input_reader(&input_reader);
    pthread_cleanup_push(cleanup_input_reader_module, &input_reader);

    while (true) {
        read_input_event(&input_reader);
        process_input_event(&input_reader.event, play_manager);
    }

    return NULL;
}