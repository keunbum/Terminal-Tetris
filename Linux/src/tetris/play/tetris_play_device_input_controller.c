#include <assert.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>

#include "debug.h"
#include "game_system/game_system_manager.h"
#include "pthread_macro.h"
#include "tetris_play_device_input_controller.h"

tetromino_in_play_status_t process_tetris_play_controller_event(device_input_t* const out_in, tetromino_manager_t* const out_tetro_man)
{
    const struct input_event* ev = &out_in->event;
    matrix_t* matrix = &out_tetro_man->matrix;
    tetromino_t* tetro = out_tetro_man->tetromino_in_play;
    tetromino_in_play_status_t ret = TETROMINO_IN_PLAY_STATUS_NULL;

    switch (ev->type) {
    case EV_ABS:
        switch (ev->code) {
        case ABS_HAT0X:
            switch (ev->value) {
            case -1:
                ret = try_move_tetromino_in_play_byone(matrix, tetro, DIR_LEFT);
                break;
            case +1:
                ret = try_move_tetromino_in_play_byone(matrix, tetro, DIR_RIGHT);
                break;
            }
            break;
        case ABS_HAT0Y:
            switch (ev->value) {
            case 1:
                ret = try_move_tetromino_in_play_byone(matrix, tetro, DIR_BOT);
                break;
            }
        }
        break;
    case EV_KEY:
        switch (ev->value) {
        case 1:
            switch (ev->code) {
            case BTN_SOUTH:
                ret = harddrop_tetromino_in_play(matrix, tetro);
                break;
            // case BTN_WEST:
            //     ret = try_piece_hold(out_tetro_man);
            //     break;
            case BTN_NORTH:
                ret = try_hold_tetromino_in_play(out_tetro_man);
                break;
            case BTN_TL:
                ret = try_rotate_tetromino_in_play(matrix, tetro, -1);
                break;
            case BTN_TR:
                ret = try_rotate_tetromino_in_play(matrix, tetro, +1);
                break;
            case BTN_MODE:
                /* Not a good logic */
                /* A pause is ideal */
                exit_cleanup_game_system(EXIT_SUCCESS);
                break;
            }
            break;
        }
        break;
    }
    return ret;
}
