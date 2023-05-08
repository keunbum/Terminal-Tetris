#ifndef __TETRIS_PLAY_DEVICE_INPUT_CONTROLLER__H
#define __TETRIS_PLAY_DEVICE_INPUT_CONTROLLER__H

#include "device_input.h"
#include "tetris_play_tetromino_manager.h"

tetromino_in_play_status_t process_controller_event(device_input_t* const out_in, tetromino_manager_t* const out_tetro_man);

#endif /* __TETRIS_PLAY_DEVICE_INPUT_CONTROLLER__H */