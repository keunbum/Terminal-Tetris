#include "tetris_play_update_tetromino_status.h"
#include "debug.h"
#include "tetris_play_tetromino_silhouette.h"

static const int GS_DX[] = { 1, 0, -1, 0, 0 };
static const int GS_DY[] = { 0, 1, 0, -1, 0 };

const wchar_t* get_tetromino_status_wstr(tetromino_status_t status)
{
    static const wchar_t* S_STRS[] = { L"TETROMINO_STATUS_NULL", L"TETROMINO_STATUS_ONTHEWALL", L"TETROMINO_STATUS_MOVE", L"TETROMINO_STATUS_ROTATE", L"TETROMINO_STATUS_ONTHEGROUND" };
    return S_STRS[status];
}

bool is_ok_tetromino_next_status(const board_t* restrict board, const tetromino_t* restrict tetro, pos_int_t npos, dir_t nrotate_dir)
{
    debug();

    my_assert(is_valid_tetromino(tetro));

    tetromino_symbol_t nsymbol = get_tetromino_symbol(tetro->symbol_id, nrotate_dir);

    traverse_symbol(i, j, nsymbol) {
        pos_int_t each_npos = { npos.x + i, npos.y + j };
        my_assert(TETRIS_PLAY_TETROMINO_POS_X_MIN <= each_npos.x);
        int ni = each_npos.x - board->pos.x;
        int nj = each_npos.y - board->pos.y;
        if (each_npos.x > TETRIS_PLAY_TETROMINO_POS_X_MAX
            || each_npos.y < TETRIS_PLAY_TETROMINO_POS_Y_MIN
            || each_npos.y > TETRIS_PLAY_TETROMINO_POS_Y_MAX
            || board->grid[ni][nj].nature != BLOCK_NATURE_EMPTY) {
            return false;
        }
    }
    return true;
}

tetromino_status_t try_move_down_tetromino_deltatime_r(board_t* const restrict out_board, tetromino_t* const restrict out_tetro, game_time_t delta_time)
{
    debug();

    my_assert(is_valid_tetromino(out_tetro));

    pos_t npos = {
        out_tetro->pos.x + GS_DX[DIR_BOT] * out_tetro->velocity * delta_time,
        out_tetro->pos.y + GS_DY[DIR_BOT] * out_tetro->velocity * delta_time
    };
    bool is_ok = is_ok_tetromino_next_status(out_board, out_tetro, get_posint(npos), out_tetro->dir);
    if (is_ok) {
        update_tetromino_pos(out_tetro, npos);
        return TETROMINO_STATUS_MOVE;
    }
    return TETROMINO_STATUS_ONTHEGROUND;
}

tetromino_status_t try_move_tetromino_byone_r(board_t* const restrict out_board, tetromino_t* const restrict out_tetro, dir_t dir)
{
    debug();

    if (!is_valid_tetromino(out_tetro)) {
        return TETROMINO_STATUS_NULL;
    }
    my_assert(out_tetro != NULL);
    pos_t npos = {
        out_tetro->pos.x + GS_DX[dir] * 1,
        out_tetro->pos.y + GS_DY[dir] * 1
    };
    bool is_ok = is_ok_tetromino_next_status(out_board, out_tetro, get_posint(npos), out_tetro->dir);
    if (is_ok) {
        update_tetromino_pos(out_tetro, npos);
        return TETROMINO_STATUS_MOVE;
    }
    return dir == DIR_BOT ? TETROMINO_STATUS_ONTHEGROUND : TETROMINO_STATUS_ONTHEWALL;
}

tetromino_status_t try_rotate_tetromino_r(board_t* const restrict out_board, tetromino_t* const restrict out_tetro, int by)
{
    debug();

    if (!is_valid_tetromino(out_tetro)) {
        return TETROMINO_STATUS_NULL;
    }
    dir_t nrotate_dir = (out_tetro->dir + by + DIR_NUM_OF_KINDS) % DIR_NUM_OF_KINDS;
    static const int S_DX[] = { 0, 0, 0 };
    static const int S_DY[] = { 0, 1, -1 };
    for (int i = 0; i < 3; ++i) {
        for (int scalar = 1; scalar <= 3; scalar++) {
            pos_t npos = {
                out_tetro->pos.x + scalar * S_DX[i],
                out_tetro->pos.y + scalar * S_DY[i]
            };
            bool is_ok = is_ok_tetromino_next_status(out_board, out_tetro, get_posint(npos), nrotate_dir);
            if (is_ok) {
                out_tetro->dir = nrotate_dir;
                update_tetromino_pos(out_tetro, npos);
                return TETROMINO_STATUS_ROTATE;
            }
        }
    }
    return TETROMINO_STATUS_ONTHEWALL;
}

tetromino_status_t harddrop_tetromino_r(board_t* const restrict out_board, tetromino_t* const out_tetro)
{
    debug();

    if (!is_valid_tetromino(out_tetro)) {
        return TETROMINO_STATUS_NULL;
    }
    update_tetromino_pos(out_tetro, get_tetromino_silhouette_pos(out_board, out_tetro));
    return TETROMINO_STATUS_ONTHEGROUND;
}
