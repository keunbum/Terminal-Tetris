#ifndef __TETRIS_PLAY_DEVICE_INPUT_MODULES__H
#define __TETRIS_PLAY_DEVICE_INPUT_MODULES__H

#include "device_input.h"
#include "tetris_play_device_input_module_controller.h"
#include "tetris_play_device_input_module_keyboard.h"
#include "tetris_play_manager.h"
#include "tetris_play_tetromino_manager.h"
#include "tetris_play_update_world.h"

// void* mainfunc_device_input_modules(void* arg);
tetromino_status_t process_input_event(device_input_t* const out_in, tetromino_manager_t* const tetro_man);

#endif /* __TETRIS_PLAY_DEVICE_INPUT_MODULES__H */