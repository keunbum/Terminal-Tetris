#ifndef __TETRIS_PLAY_OBJECT__H
#define __TETRIS_PLAY_OBJECT__H

#include "pos.h"
#include "tetris/play/tetris_play_fps.h"

typedef void (*updatable_func_t)(void* arg);
typedef void (*drawable_func_t)(void* arg, game_time_t delta_time);

#endif /* __TETRIS_PLAY_OBJECT__H */