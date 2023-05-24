#include <assert.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "debug.h"
#include "game_system/game_system_manager.h"
#include "pthread_macro.h"
#include "tetris_play_device_input_keyboard.h"
#include "tetris_play_tetromino_manager.h"

tetromino_in_play_status_t process_tetris_play_keyboard_event(device_input_t* const out_in, tetromino_manager_t* const tetro_man)
{
    const struct input_event* ev = &out_in->event;
    matrix_t* matrix = &tetro_man->matrix;
    tetromino_t* tetro = tetro_man->tetromino_in_play;
    tetromino_in_play_status_t ret = TETROMINO_IN_PLAY_STATUS_NULL;

    switch (ev->type) {
    case EV_KEY:
        switch (ev->value) {
        case 1:
            switch (ev->code) {
            case KEY_DOWN:
                ret = try_move_tetromino_in_play_byone(matrix, tetro, DIR_BOT);
                break;
            case KEY_LEFT:
                ret = try_move_tetromino_in_play_byone(matrix, tetro, DIR_LEFT);
                break;
            case KEY_RIGHT:
                ret = try_move_tetromino_in_play_byone(matrix, tetro, DIR_RIGHT);
                break;
            case KEY_UP:
                /* intentional fallthrough */
            case KEY_X:
                ret = try_rotate_tetromino_in_play(matrix, tetro, +1);
                break;
            case KEY_SPACE:
                ret = harddrop_tetromino_in_play(matrix, tetro);
                break;
            case KEY_Z:
                ret = try_rotate_tetromino_in_play(matrix, tetro, -1);
                break;
            case KEY_C:
                ret = try_hold_tetromino_in_play(tetro_man);
                break;
            case KEY_ESC:
                /* Not a good logic */
                /* A pause is ideal */
                exit_cleanup_game_system(EXIT_SUCCESS);
                break;
            }
            break;
        case 2:
            switch (ev->code) {
            case KEY_DOWN:
                try_move_tetromino_in_play_byone(matrix, tetro, DIR_BOT);
                break;
            case KEY_LEFT:
                try_move_tetromino_in_play_byone(matrix, tetro, DIR_LEFT);
                break;
            case KEY_RIGHT:
                try_move_tetromino_in_play_byone(matrix, tetro, DIR_RIGHT);
                break;
            }
            break;
        }
        break;
    }
    return ret;
}
