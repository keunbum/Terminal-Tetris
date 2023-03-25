

#include "simulate.h"
#include "game/game_play/tetromino/tetromino.h"

/*
static void draw_a_default_tetromino_at(int id, int sx, int sy)
{
    tetromino_t t = {
        .tetromino_id = id,
        .dir = DIR_BOT,
        .color = COLOR_WHITE,
    };
    draw_a_tetromino_at(&t, sx, sy);
}
*/

void move_tetromino(tetromino_t* const t)
{
    static const pos_t S_DX[] = { 1, 0, -1, 0 };
    static const pos_t S_DY[] = { 0, 1, 0, -1 };

    pos_t npos_x = t->pos_x + t->velocity * S_DX[t->dir];
    pos_t npos_y = t->pos_y + t->velocity * S_DY[t->dir];
}