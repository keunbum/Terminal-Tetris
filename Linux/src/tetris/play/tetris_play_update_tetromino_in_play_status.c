#include "tetris_play_update_tetromino_in_play_status.h"
#include "debug.h"
#include "tetris_play_ghost_piece.h"

static const int GS_DX[] = { 1, 0, -1, 0, 0 };
static const int GS_DY[] = { 0, 1, 0, -1, 0 };

const wchar_t* get_tetromino_in_play_status_wstr(tetromino_in_play_status_t status)
{
    static const wchar_t* S_STRS[] = { L"TETROMINO_IN_PLAY_STATUS_NULL", L"TETROMINO_IN_PLAY_STATUS_ONTHEWALL", L"TETROMINO_IN_PLAY_STATUS_MOVE", L"TETROMINO_IN_PLAY_STATUS_ROTATE", L"TETROMINO_IN_PLAY_STATUS_ONTHEGROUND" };
    return S_STRS[status];
}

bool is_ok_tetromino_in_play_next_status(const matrix_t* restrict matrix, const tetromino_t* restrict tetro, pos_int_t npos, dir_t nrotate_dir)
{
    tetromino_shape_t nshape = get_tetromino_shape(tetro->shape_id, nrotate_dir);

    bool is_ok = true;
    traverse_shape(i, j, nshape) {
        int ni = npos.x + i - matrix->pos.x;
        int nj = npos.y + j - matrix->pos.y;
        is_ok &= matrix->grid[ni][nj].nature == BLOCK_NATURE_EMPTY;
    }
    return is_ok;
}

tetromino_in_play_status_t try_move_down_tetromino_in_play_deltatime(matrix_t* const restrict out_board, tetromino_t* const restrict out_tetro, game_time_t delta_time)
{
    pos_t npos = {
        out_tetro->pos.x + GS_DX[DIR_BOT] * out_tetro->velocity * delta_time,
        out_tetro->pos.y + GS_DY[DIR_BOT] * out_tetro->velocity * delta_time
    };
    bool is_ok = is_ok_tetromino_in_play_next_status(out_board, out_tetro, get_posint(npos), out_tetro->dir);
    if (is_ok) {
        update_tetromino_pos(out_tetro, npos);
        return TETROMINO_IN_PLAY_STATUS_MOVE;
    }
    return TETROMINO_IN_PLAY_STATUS_ONTHEGROUND;
}

tetromino_in_play_status_t try_move_tetromino_in_play_byone(matrix_t* const restrict out_board, tetromino_t* const restrict out_tetro, dir_t dir)
{
    if (!is_valid_tetromino(out_tetro)) {
        return TETROMINO_IN_PLAY_STATUS_NULL;
    }
    pos_t npos = {
        out_tetro->pos.x + GS_DX[dir] * TETRIS_PLAY_TETROMINO_IN_PLAY_UNIT_DISTANCE,
        out_tetro->pos.y + GS_DY[dir] * TETRIS_PLAY_TETROMINO_IN_PLAY_UNIT_DISTANCE
    };
    bool is_ok = is_ok_tetromino_in_play_next_status(out_board, out_tetro, get_posint(npos), out_tetro->dir);
    if (is_ok) {
        update_tetromino_pos(out_tetro, npos);
        return TETROMINO_IN_PLAY_STATUS_MOVE;
    }
    return dir == DIR_BOT ? TETROMINO_IN_PLAY_STATUS_ONTHEGROUND : TETROMINO_IN_PLAY_STATUS_ONTHEWALL;
}

tetromino_in_play_status_t try_rotate_tetromino_in_play(matrix_t* const restrict out_board, tetromino_t* const restrict out_tetro, int by)
{
    if (!is_valid_tetromino(out_tetro)) {
        return TETROMINO_IN_PLAY_STATUS_NULL;
    }
    dir_t nrotate_dir = (out_tetro->dir + by + DIR_NUM_OF_KINDS) % DIR_NUM_OF_KINDS;
    static const int S_DX[] = { 0, 0, 0 };
    static const int S_DY[] = { 0, 1, -1 };
    for (int i = 0; i < 3; ++i) {
        for (int scalar = 1; scalar <= 2; scalar++) {
            pos_t npos = {
                out_tetro->pos.x + scalar * S_DX[i],
                out_tetro->pos.y + scalar * S_DY[i]
            };
            bool is_ok = is_ok_tetromino_in_play_next_status(out_board, out_tetro, get_posint(npos), nrotate_dir);
            if (is_ok) {
                out_tetro->dir = nrotate_dir;
                update_tetromino_pos(out_tetro, npos);
                return TETROMINO_IN_PLAY_STATUS_ROTATE;
            }
        }
    }
    return TETROMINO_IN_PLAY_STATUS_ONTHEWALL;
}

tetromino_in_play_status_t harddrop_tetromino_in_play(matrix_t* const restrict out_board, tetromino_t* const restrict out_tetro)
{
    if (!is_valid_tetromino(out_tetro)) {
        return TETROMINO_IN_PLAY_STATUS_NULL;
    }
    update_tetromino_pos(out_tetro, get_ghost_piece_pos(out_board, out_tetro));
    return TETROMINO_IN_PLAY_STATUS_ONTHEGROUND;
}
