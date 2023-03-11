/*
 * Header related to screen output.
 */

#ifndef __DISPLAY__H
#define __DISPLAY__H

#include <wchar.h>

#include "cursor.h"
#include "tetromino/tetromino.h"

#define SCREEN_HEIGHT (30)
#define SCREEN_WIDTH (44)
#define SCREEN_START_X (0)
#define SCREEN_START_Y (0)

#define INSIDE_AREA_HEIGHT (20)
#define INSIDE_AREA_WIDTH (20)
#define INSIDE_AREA_START_X (5)
#define INSIDE_AREA_START_Y (12)

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

#define draw_empty_line() wprintf(L"\n")

void draw_unit_matrix(wchar_t);
void draw_whole_screen_at(int, int);

void draw_a_default_tetromino_at(int id, int sx, int sy);
void draw_a_tetromino_at(const tetromino_t *, int, int);

void draw_time_at(int, int, int);

#endif /* __DISPLAY__H */