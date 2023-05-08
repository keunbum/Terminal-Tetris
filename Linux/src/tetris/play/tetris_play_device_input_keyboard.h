#ifndef __TETRIS_PLAY_DEVICE_INPUT_KEYBOARD__H
#define __TETRIS_PLAY_DEVICE_INPUT_KEYBOARD__H

#include "tetris_play_tetromino_manager.h"
#include "device_input.h"

tetromino_in_play_status_t process_keyboard_event(device_input_t* const out_in, tetromino_manager_t* const tetro_man);

#endif /* __TETRIS_PLAY_DEVICE_INPUT_KEYBOARD__H */