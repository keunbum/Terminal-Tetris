#ifndef __TETRIS_PLAY_DEVICE_INPUT__H
#define __TETRIS_PLAY_DEVICE_INPUT__H

#include "tetris_play_device_input_keyboard.h"
#include "tetris_play_tetromino_manager.h"

tetromino_in_play_status_t process_input_event(device_input_t* const out_in, tetromino_manager_t* const tetro_man);

#endif /* __TETRIS_PLAY_DEVICE_INPUT__H */