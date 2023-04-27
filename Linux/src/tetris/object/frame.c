#include "frame.h"
#include "debug.h"
#include "draw/draw_tool.h"

void init_frame(
    frame_t* const next_frame,
    int height_wprint, int width_wprint,
    pos_int_t pos_wprint,
    title_t title,
    block_wprint_t hor_block, block_wprint_t ver_block,
    block_wprint_t corner_top_lft, block_wprint_t corner_top_rgt, block_wprint_t corner_bot_lft, block_wprint_t corner_bot_rgt)
{
    debug();

    next_frame->height_wprint = height_wprint;
    next_frame->width_wprint = width_wprint;

    next_frame->pos_wprint = pos_wprint;

    next_frame->title = title;

    next_frame->hor_block = hor_block;
    next_frame->ver_block = ver_block;
    next_frame->corner_top_lft = corner_top_lft;
    next_frame->corner_top_rgt = corner_top_rgt;
    next_frame->corner_bot_lft = corner_bot_lft;
    next_frame->corner_bot_rgt = corner_bot_rgt;
}

void cleanup_frame(frame_t* const next_frame)
{
    debug();

    /* do nothing */
    (void)next_frame;
}

void wdraw_frame(const frame_t* next_frame, int title_pos_y_offset)
{
    debug();
    
    my_assert(next_frame != NULL);

    if (next_frame->title != NULL) {
        wprintf_at_r(next_frame->pos_wprint.x - 1, next_frame->pos_wprint.y + title_pos_y_offset, next_frame->title);
    }

    wdraw_boundary_at_with(next_frame->hor_block,
        next_frame->ver_block,
        next_frame->height_wprint,
        next_frame->width_wprint,
        next_frame->pos_wprint.x,
        next_frame->pos_wprint.y,
        (wchar_t)next_frame->corner_top_lft,
        (wchar_t)next_frame->corner_top_rgt,
        (wchar_t)next_frame->corner_bot_lft,
        (wchar_t)next_frame->corner_bot_rgt);
}