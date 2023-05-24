#ifndef __TETRIS_PLAY_DEVICE_INPUT__H
#define __TETRIS_PLAY_DEVICE_INPUT__H

#include "device_input.h"
#include "tetris_play_tetromino_manager.h"

typedef tetromino_in_play_status_t (*process_device_input_event_func_t)(device_input_t* const, tetromino_manager_t* const);

typedef struct {
    device_input_t in;
    process_device_input_event_func_t func;
} tetris_play_device_input_t;

void init_tetris_play_device_input(tetris_play_device_input_t* const out_tin, int device_event_num, int flags, process_device_input_event_func_t func);
void cleanup_tetris_play_device_input(tetris_play_device_input_t* const out_tin);
tetromino_in_play_status_t new_process_tetris_play_device_event(tetris_play_device_input_t* const out_tin, tetromino_manager_t* const tetro_man);

#endif /* __TETRIS_PLAY_DEVICE_INPUT__H */