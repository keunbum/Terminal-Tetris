#include "frame.h"
#include "debug.h"
#include "draw/draw_tool.h"

void init_frame(
    frame_t* const out_frame,
    int height_wprint, int width_wprint,
    pos_int_t pos_wprint,
    title_t title_or_null,
    block_wprint_t hor_block, block_wprint_t ver_block,
    block_wprint_t corner_top_lft_block, block_wprint_t corner_top_rgt_block, block_wprint_t corner_bot_lft_block, block_wprint_t corner_bot_rgt_block)
{
    out_frame->height_wprint = height_wprint;
    out_frame->width_wprint = width_wprint;

    out_frame->pos_wprint = pos_wprint;

    out_frame->title = title_or_null;

    out_frame->hor_block = hor_block;
    out_frame->ver_block = ver_block;
    
    out_frame->corner_top_lft_block = corner_top_lft_block;
    out_frame->corner_top_rgt_block = corner_top_rgt_block;
    out_frame->corner_bot_lft_block = corner_bot_lft_block;
    out_frame->corner_bot_rgt_block = corner_bot_rgt_block;
}

void cleanup_frame(frame_t* const out_frame)
{
    /* do nothing */
    (void)out_frame;
}

void wdraw_frame(const frame_t* frame, int title_pos_y_offset)
{
    if (frame->title != NULL) {
        wprintf_at_r(frame->pos_wprint.x - 1, frame->pos_wprint.y + title_pos_y_offset, frame->title);
    }

    wdraw_boundary_at_with(frame->hor_block,
        frame->ver_block,
        frame->height_wprint,
        frame->width_wprint,
        frame->pos_wprint.x,
        frame->pos_wprint.y,
        (wchar_t)frame->corner_top_lft_block,
        (wchar_t)frame->corner_top_rgt_block,
        (wchar_t)frame->corner_bot_lft_block,
        (wchar_t)frame->corner_bot_rgt_block);
}