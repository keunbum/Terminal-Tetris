#include "frame.h"
#include "debug.h"
#include "draw/draw_tool.h"

void init_frame(
    frame_t* const frame,
    int height_wprint, int width_wprint,
    pos_t pos_wprint,
    title_t title,
    block_wprint_t hor_block, block_wprint_t ver_block,
    block_wprint_t corner_top_lft, block_wprint_t corner_top_rgt, block_wprint_t corner_bot_lft, block_wprint_t corner_bot_rgt)
{
    frame->height_wprint = height_wprint;
    frame->width_wprint = width_wprint;

    frame->pos_wprint = pos_wprint;

    frame->title = title;

    frame->hor_block = hor_block;
    frame->ver_block = ver_block;
    frame->corner_top_lft = corner_top_lft;
    frame->corner_top_rgt = corner_top_rgt;
    frame->corner_bot_lft = corner_bot_lft;
    frame->corner_bot_rgt = corner_bot_rgt;
}

void wdraw_frame(const frame_t* frame, int title_pos_x_offset)
{
    my_assert(frame != NULL);

    if (frame->title != NULL) {
        wprintf_at_r((int)frame->pos_wprint.x - 1, (int)frame->pos_wprint.y + title_pos_x_offset, frame->title);
    }

    wdraw_boundary_at_with(frame->hor_block,
        frame->ver_block,
        (int)frame->height_wprint,
        (int)frame->width_wprint,
        (int)frame->pos_wprint.x,
        (int)frame->pos_wprint.y,
        (wchar_t)frame->corner_top_lft,
        (wchar_t)frame->corner_top_rgt,
        (wchar_t)frame->corner_bot_lft,
        (wchar_t)frame->corner_bot_rgt);
}