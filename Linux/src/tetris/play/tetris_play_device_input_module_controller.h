#ifndef __TETRIS_PLAY_DEVICE_INPUT_MODULE_CONTROLLER__H
#define __TETRIS_PLAY_DEVICE_INPUT_MODULE_CONTROLLER__H

#include "device_input.h"

tetromino_status_t process_controller_event(device_input_t* const out_in, tetromino_manager_t* const out_tetro_man);

#endif /* __TETRIS_PLAY_DEVICE_INPUT_MODULE_CONTROLLER__H */