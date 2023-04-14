#ifndef __SCREEN__H
#define __SCREEN__H

#include "draw/draw_tool.h"

#include "pos.h"
// #include "tetris_play_object.h"

typedef struct {
    const wchar_t hor_line;
    const wchar_t ver_line;
    const wchar_t corner_top_left;
    const wchar_t corner_top_right;
    const wchar_t corner_bot_left;
    const wchar_t corner_bot_right;

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