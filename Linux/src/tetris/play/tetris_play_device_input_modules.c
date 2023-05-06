#include "tetris_play_device_input_modules.h"

tetromino_status_t process_input_event(device_input_t* const out_in, tetromino_manager_t* const tetro_man)
{
    return process_keyboard_event(out_in, tetro_man);
}