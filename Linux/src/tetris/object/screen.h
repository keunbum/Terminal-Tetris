#ifndef __SCREEN__H
#define __SCREEN__H

#include "pos.h"
// #include "tetris_play_object.h"

typedef struct {
    const pos_t pos;
    const pos_t pos_wprint;
    // drawable_func_t draw;

    const int height;
    const int width;
    const int height_wprint;
    const int width_wprint;
} screen_t;

void wdraw_screen(const screen_t* screen);

#endif /* __SCREEN__H */