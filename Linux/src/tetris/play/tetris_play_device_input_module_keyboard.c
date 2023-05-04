#include <assert.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "debug.h"
#include "device_input.h"
#include "pthread_macro.h"
#include "tetris_play_device_input_module_keyboard.h"
#include "tetris_play_tetromino_manager.h"

static inline int get_keyboard_event_num(void)
{
    FILE* pipe = popen("grep -E 'Handlers|EV=' /proc/bus/input/devices | grep -B1 'EV=120013' | grep -Eo 'event[0-9]+'", "r");
    if (pipe == NULL) {
        handle_error("popen() error");
    }
    int ret = 0;
    if (fscanf(pipe, "event%d\n", &ret) != 1) {
        handle_error("fscanf() error");
    }
    pclose(pipe);
    return ret;
}

tetromino_status_t process_keyboard_event(device_input_t* const out_in, tetromino_manager_t* const tetro_man)
{
    const struct input_event* ev = &out_in->event;
    board_t* board = &tetro_man->board;
    tetromino_t* tetro = tetro_man->tetro_main;
    tetromino_status_t ret = TETROMINO_STATUS_NULL;

    switch (ev->type) {
    case EV_KEY:
        switch (ev->value) {
        case 1:
            switch (ev->code) {
            case KEY_DOWN:
                ret = try_move_tetromino_byone_r(board, tetro, DIR_BOT);
                break;
            case KEY_LEFT:
                ret = try_move_tetromino_byone_r(board, tetro, DIR_LEFT);
                break;
            case KEY_RIGHT:
                ret = try_move_tetromino_byone_r(board, tetro, DIR_RIGHT);
                break;
            case KEY_UP:
                /* intentional fallthrough */
            case KEY_X:
                ret = try_rotate_tetromino_r(board, tetro, +1);
                break;
            case KEY_SPACE:
                ret = harddrop_tetromino_r(board, tetro);
                break;
            case KEY_Z:
                ret = try_rotate_tetromino_r(board, tetro, -1);
                break;
            case KEY_C:
                ret = try_swap_tetromino_hold(tetro_man);
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
                try_move_tetromino_byone_r(board, tetro, DIR_BOT);
                break;
            case KEY_LEFT:
                try_move_tetromino_byone_r(board, tetro, DIR_LEFT);
                break;
            case KEY_RIGHT:
                try_move_tetromino_byone_r(board, tetro, DIR_RIGHT);
                break;
            }
            break;
        }
        break;
    }
    return ret;
}

// void* mainfunc_device_input_module_keyboard(void* arg)
// {
//     debug();

//     tetris_play_manager_t* const play_manager = (tetris_play_manager_t*)arg;
//     device_input_t in;
//     // init_device_input(&in, DEVICE_INPUT_KEYBOARD, O_RDONLY);
//     init_device_input(&in, get_keyboard_event_num(), O_RDONLY);
//     pthread_cleanup_push(callback_cleanup_device_input, &in);

//     while (true) {
//         read_device_input_event(&in);
//         lock_tetromino_manager(&play_manager->tetro_man);
//         tetromino_status_t res = process_keyboard_event_thread(&in, &play_manager->tetro_man);
//         process_tetromino_status(res, play_manager);
//         unlock_tetromino_manager(&play_manager->tetro_man);
//     }

//     pthread_cleanup_pop(1);

//     return NULL;
// }
