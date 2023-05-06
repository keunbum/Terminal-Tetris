#include <assert.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>

#include "debug.h"
#include "pthread_macro.h"
#include "tetris/play/tetris_play_update_world.h"
#include "tetris_play_device_input_module_controller.h"

tetromino_status_t process_controller_event(device_input_t* const out_in, tetromino_manager_t* const out_tetro_man)
{
    const struct input_event* ev = &out_in->event;
    board_t* board = &out_tetro_man->board;
    tetromino_t* tetro = out_tetro_man->main_piece;
    tetromino_status_t ret = TETROMINO_STATUS_NULL;

    switch (ev->type) {
    case EV_ABS:
        switch (ev->code) {
        case ABS_HAT0X:
            switch (ev->value) {
            case -1:
                ret = try_move_tetromino_byone_r(board, tetro, DIR_LEFT);
                break;
            case +1:
                ret = try_move_tetromino_byone_r(board, tetro, DIR_RIGHT);
                break;
            }
            break;
        case ABS_HAT0Y:
            switch (ev->value) {
            case 1:
                ret = try_move_tetromino_byone_r(board, tetro, DIR_BOT);
                break;
            }
        }
        break;
    case EV_KEY:
        switch (ev->value) {
        case 1:
            switch (ev->code) {
            case BTN_SOUTH:
                ret = harddrop_tetromino_r(board, tetro);
                break;
            // case BTN_WEST:
            //     ret = try_swap_tetromino_hold(out_tetro_man);
            //     break;
            case BTN_NORTH:
                ret = try_swap_tetromino_hold(out_tetro_man);
                break;
            case BTN_TL:
                ret = try_rotate_tetromino_r(board, tetro, -1);
                break;
            case BTN_TR:
                ret = try_rotate_tetromino_r(board, tetro, +1);
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
