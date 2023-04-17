#include "tetris_play_update_tetromino_status.h"
#include "debug.h"

static const int G_S_DX[] = { 1, 0, -1, 0 };
static const int G_S_DY[] = { 0, 1, 0, -1 };

// /* return tetromino's status when moving left, right, or down.
//    implement the rotation operation separately. */
tetromino_try_status_t try_tetromino_next_status(const board_t* restrict board, const tetromino_t* restrict tetro, pos_t npos, dir_t ndir)
{
    debug();

    tetromino_matrix_t matrix = get_tetromino_matrix(tetro->symbol_id, ndir);
    tetromino_matrix_n_t n = get_tetromino_matrix_n(tetro->symbol_id);

    ewprintf("TETRIS_PLAY_TETROMINO_POS_X_MIN: %d\n", TETRIS_PLAY_TETROMINO_POS_X_MIN);
    ewprintf("TETRIS_PLAY_TETROMINO_POS_X_MAX: %d\n", TETRIS_PLAY_TETROMINO_POS_X_MAX);
    ewprintf("TETRIS_PLAY_TETROMINO_POS_Y_MIN: %d\n", TETRIS_PLAY_TETROMINO_POS_Y_MIN);
    ewprintf("TETRIS_PLAY_TETROMINO_POS_Y_MAX: %d\n", TETRIS_PLAY_TETROMINO_POS_Y_MAX);

    for (int idx = 0; idx < n * n; ++idx) {
        if (is_empty_block(matrix, idx)) {
            continue;
        }
        int i = idx / n;
        int j = idx % n;
        pos_t each_npos = { npos.x + i, npos.y + j };
        int nx = (int)each_npos.x;
        int ny = (int)each_npos.y;
        ewprintf("i, j: (%d, %d)\n", i, j);  
        ewprintf("nx, ny: (%d, %d)\n", nx, ny);  
        my_assert(TETRIS_PLAY_TETROMINO_POS_X_MIN <= nx);
        if (ny < TETRIS_PLAY_TETROMINO_POS_Y_MIN || ny > TETRIS_PLAY_TETROMINO_POS_Y_MAX) {
            ewprintf("hi1\n");
            return TETROMINO_TRY_STATUS_INPLACE;
        }
        if (nx > TETRIS_PLAY_TETROMINO_POS_X_MAX) {
            ewprintf("hi2\n");
            return TETROMINO_TRY_STATUS_ONTHEGROUND;
        }
        my_assert(nx <= TETRIS_PLAY_TETROMINO_POS_X_MAX);
        my_assert(TETRIS_PLAY_TETROMINO_POS_Y_MIN <= ny && ny <= TETRIS_PLAY_TETROMINO_POS_Y_MAX);
        int ni = nx - (int)board->pos.x;
        int nj = ny - (int)board->pos.y;
        my_assert(1 <= ni && ni <= board->height - 2);
        my_assert(1 <= nj && nj <= board->width - 2);
        if (board->grid[ni][nj].nature != BLOCK_NATURE_EMPTY) {
            ewprintf("hi3\n");
            return TETROMINO_TRY_STATUS_ONTHEGROUND;
        }
    }
    ewprintf("hi4\n");
    return TETROMINO_TRY_STATUS_MOVED;
}

tetromino_try_status_t try_move_tetromino_deltatime_r(board_t* const restrict out_board, tetromino_t* const restrict out_tetro, dir_t dir, game_time_t delta_time)
{
    debug();

    my_assert(is_valid_tetromino(out_tetro));

    pos_t npos = {
        out_tetro->pos.x + G_S_DX[dir] * (out_tetro->velocity * delta_time),
        out_tetro->pos.y + G_S_DY[dir] * (out_tetro->velocity * delta_time)
    };

    tetromino_try_status_t res = try_tetromino_next_status(out_board, out_tetro, npos, out_tetro->dir);
    if (res == TETROMINO_TRY_STATUS_MOVED) {
        out_tetro->pos = npos;
        out_tetro->pos_wprint = get_tetromino_poswprint(out_tetro->pos);
    }
    return res;
}

tetromino_try_status_t try_move_tetromino_byone_r(board_t* const restrict out_board, tetromino_t* const restrict out_tetro, dir_t dir)
{
    debug();
    // my_assert(is_valid_tetromino(out_tetro));
    if (!is_valid_tetromino(out_tetro)) {
        return TETROMINO_TRY_STATUS_NULL;
    }
    pos_t npos = {
        out_tetro->pos.x + G_S_DX[dir] * 1,
        out_tetro->pos.y + G_S_DY[dir] * 1
    };
    ewprintf("For tetro-%d\n", out_tetro->id);
    ewprintf("symbol: %lc\n", get_symbol_wstr(out_tetro->symbol_id));
    ewprintf("dir: %ls\n", get_dir_wstr(dir));
    ewprintf("pos: (%d, %d)\n", (int)out_tetro->pos.x, (int)out_tetro->pos.y);
    ewprintf("expected npos: (%d, %d)\n", (int)npos.x, (int)npos.y);
    tetromino_try_status_t res = try_tetromino_next_status(out_board, out_tetro, npos, out_tetro->dir);
    ewprintf("tetromino_try_status: %ls\n", get_tetomino_try_status_wstr(res));
    if (res == TETROMINO_TRY_STATUS_MOVED) {
        out_tetro->pos = npos;
    }
    ewprintf("after pos: (%d, %d)\n", (int)out_tetro->pos.x, (int)out_tetro->pos.y);
    out_tetro->pos_wprint = get_tetromino_poswprint(out_tetro->pos);
    ewprintf("after poswprint: (%d, %d)\n", (int)out_tetro->pos_wprint.x, (int)out_tetro->pos_wprint.y);
    return res;
}

tetromino_try_status_t try_rotate_tetromino_r(board_t* const restrict out_board, tetromino_t* const restrict out_tetro, int by)
{
    debug();
    // my_assert(is_valid_tetromino(out_tetro));
    if (!is_valid_tetromino(out_tetro)) {
        return TETROMINO_TRY_STATUS_NULL;
    }
    dir_t ndir = (out_tetro->dir + by + DIR_NUM_OF_KINDS) % DIR_NUM_OF_KINDS;
    tetromino_try_status_t res = try_tetromino_next_status(out_board, out_tetro, out_tetro->pos, ndir);
    if (res == TETROMINO_TRY_STATUS_MOVED) {
        out_tetro->dir = ndir;
    }
    return res;
}

tetromino_try_status_t harddrop_tetromino_r(tetromino_t* const out_tetro)
{
    debug();

    (void)out_tetro;
    return TETROMINO_TRY_STATUS_MOVED;
}
