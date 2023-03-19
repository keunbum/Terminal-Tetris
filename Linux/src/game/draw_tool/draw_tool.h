/*
 * Header related to screen output.
 */

#ifndef __DRAW_TOOL__H
#define __DRAW_TOOL__H

#include <wchar.h>

#include "game/game_play/common/tetromino/tetromino.h"

#define UNIT_MATRIX_CORNER_TOP_LEFT (0x2554)
#define UNIT_MATRIX_CORNER_TOP_RIGHT (0x2557)
#define UNIT_MATRIX_CORNER_BOT_LEFT (0x255A)
#define UNIT_MATRIX_CORNER_BOT_RIGHT (0x255D)

#define UNIT_MATRIX_CORNER_TOP_LEFT_THIN (0x250F)
#define UNIT_MATRIX_CORNER_TOP_RIGHT_THIN (0x2513)
#define UNIT_MATRIX_CORNER_BOT_LEFT_THIN (0x2517)
#define UNIT_MATRIX_CORNER_BOT_RIGHT_THIN (0x251B)

#define UNIT_MATRIX_HOR_LINE (0x2550)
#define UNIT_MATRIX_VER_LINE (0x2551)

#define UNIT_MATRIX_HOR_LINE_THIN (0x2501)
#define UNIT_MATRIX_VER_LINE_THIN (0x2503)

#define draw_newline() wprintf(L"\n")

void draw_row_matrix_at(wchar_t, int, int, int);
void draw_boundary_at_with(wchar_t, wchar_t, int, int, int, int, wchar_t, wchar_t, wchar_t, wchar_t);
void draw_boundary_at(wchar_t, wchar_t, int, int, int, int);
void draw_row_blocks(const block_t*);

#endif /* __DRAW_TOOL__H */