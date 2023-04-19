#ifndef __FRAME__H
#define __FRAME__H

#include "block.h"
#include "pos.h"

typedef wchar_t* title_t;

typedef struct {
    int height_wprint;
    int width_wprint;

    pos_int_t pos_wprint;

    title_t title;

    block_wprint_t hor_block;
    block_wprint_t ver_block;
    block_wprint_t corner_top_lft;
    block_wprint_t corner_top_rgt;
    block_wprint_t corner_bot_lft;
    block_wprint_t corner_bot_rgt;
} frame_t;

void init_frame(
    frame_t* const frame,
    int height_wprint, int width_wprint,
    pos_int_t pos_wprint,
    const title_t title,
    block_wprint_t hor_block, block_wprint_t ver_block,
    block_wprint_t corner_top_lft, block_wprint_t corner_top_rgt, block_wprint_t corner_bot_lft, block_wprint_t corner_bot_rgt);
void cleanup_frame(frame_t* const frame);    
void wdraw_frame(const frame_t* frame, int title_pos_x_offset);

#endif /* __FRAME__H */