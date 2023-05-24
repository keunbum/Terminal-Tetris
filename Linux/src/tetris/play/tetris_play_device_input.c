#include "tetris_play_device_input.h"

void init_tetris_play_device_input(tetris_play_device_input_t* const out_tin, int device_event_num, int flags, process_device_input_event_func_t func)
{
    init_device_input(&out_tin->in, device_event_num, flags);
    out_tin->func = func;
}

void cleanup_tetris_play_device_input(tetris_play_device_input_t* const out_tin)
{
    cleanup_device_input(&out_tin->in);
}

tetromino_in_play_status_t new_process_tetris_play_device_event(tetris_play_device_input_t* const out_tin, tetromino_manager_t* const tetro_man)
{
    return out_tin->func(&out_tin->in, tetro_man);
}