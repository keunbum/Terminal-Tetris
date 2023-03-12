/*
 * Header related to screen output.
 */

#ifndef __DRAW_MANAGER__H
#define __DRAW_MANAGER__H

#include <wchar.h>

#include "cursor.h"
#include "tetromino/tetromino.h"

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

//void draw_unit_matrix(wchar_t);
void draw_whole_screen_at(int, int);

void draw_a_tetromino_at(const tetromino_t *, int, int);
void draw_a_default_tetromino_at(int id, int sx, int sy);

void draw_game_play_timer_at(int, int, int);

#endif /* __DRAW_MANAGER__H */