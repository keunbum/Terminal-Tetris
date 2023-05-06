#ifndef __TETRIS_PLAY_DEVICE_INPUT_MODULE_KEYBOARD__H
#define __TETRIS_PLAY_DEVICE_INPUT_MODULE_KEYBOARD__H

#include "tetris/play/tetris_play_update_world.h"
#include "device_input.h"

tetromino_status_t process_keyboard_event(device_input_t* const out_in, tetromino_manager_t* const tetro_man);

#endif /* __TETRIS_PLAY_DEVICE_INPUT_MODULE_KEYBOARD__H */