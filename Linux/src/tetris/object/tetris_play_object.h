#ifndef __TETRIS_PLAY_OBJECT__H
#define __TETRIS_PLAY_OBJECT__H

#include "pos.h"
#include "tetris/tetris_play_fps.h"

typedef struct {
    pos_t pos;
} tetris_play_object_t;

typedef void (*updatable_func_t)(void* arg);
typedef void (*drawable_func_t)(void* arg, game_time_t delta_time);

typedef struct {
    pos_t pos;
    const updatable_func_t update;
} tetris_play_uobject_t;

typedef struct {
    const drawable_func_t draw;
} tetris_play_dobject_t;

typedef struct {
    pos_t pos;
    const updatable_func_t update;
    const drawable_func_t draw;
} tetris_play_udobject_t;

#endif /* __TETRIS_PLAY_OBJECT__H */