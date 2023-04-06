#include <stdio.h>

#include "debug.h"
#include "renderer.h"
#include "tetris_play_scene.h"

static inline pos_t get_pos_wprint(pos_t pos)
{
    pos_t ret = { pos.x + TETRIS_PLAY_BOARD_START_POS_X_WPRINT, 2 * pos.y + TETRIS_PLAY_BOARD_START_POS_Y_WPRINT };
    return ret;
}

static inline void render_a_block(pos_t pos, wchar_t block_wprint)
{
    pos_t pos_wprint = get_pos_wprint(pos);
    if (pos_wprint.x < TETRIS_PLAY_BOARD_START_POS_X_WPRINT) {
        return;
    }
    wdraw_unit_matrix_at(block_wprint, (int) pos_wprint.x, (int) pos_wprint.y);
    //wprintf_at((int) pos_wprint.x, (int) pos_wprint.y, L"%lc", block_wprint);
}

static void render_a_tetromino(const tetromino_t* tetro, wchar_t block_wprint)
{
    debug();

    my_assert(tetro != NULL);

    const tetromino_symbol_t* symbol = G_TETROMINO_SYMBOLS + tetro->symbol_id;
    for (int i = 0; i < symbol->height; ++i) {
        const block_t* row = symbol->block_matrix[i];
        for (int j = 0; row[j]; ++j) {
            if (row[j] == BLOCK_T_FALSE) {
                continue;
            }
            {
                pos_t each_ground_pos = { tetro->ground_pos.x + i, tetro->ground_pos.y + j };
                render_a_block(each_ground_pos, BLOCK_WPRINT_LIGHT_LARGE_SQUARE);
            }
            {
                pos_t each_pos = { tetro->pos.x + i, tetro->pos.y + j };
                render_a_block(each_pos, block_wprint);
            }
        }
    }
}

// static void render_a_tetromino_at(const tetromino_t* tetro, wchar_t block_wprint, pos_t pos)
// {
//     debug();

//     my_assert(tetro != NULL);

//     const tetromino_symbol_t* symbol = G_TETROMINO_SYMBOLS + tetro->symbol_id;
//     const int x_wprint_offset = TETRIS_PLAY_BOARD_START_POS_X_WPRINT;
//     const int y_wprint_offset = TETRIS_PLAY_BOARD_START_POS_Y_WPRINT;
//     for (int i = 0; i < symbol->height; ++i) {
//         const block_t* row = symbol->block_matrix[i];
//         for (int j = 0; row[j]; ++j) {
//             if (row[j] == BLOCK_T_FALSE) {
//                 continue;
//             }
//             pos_t each_pos_wprint = { pos.x + i + x_wprint_offset, 2 * (pos.y + j) + y_wprint_offset };
//             if (each_pos_wprint.x < TETRIS_PLAY_BOARD_START_POS_X_WPRINT) {
//                 continue;
//             }
//             pos_t each_ground_pos_wprint = { }
//             wprintf_at((int)each_pos_wprint.x, (int)each_pos_wprint.y, L"%lc", block_wprint);
//         }
//     }
// }

// static inline void render_a_tetromino_at_r(const tetromino_t* tetro, wchar_t block_wprint, pos_t pos)
// {
//     debug();

//     pthread_mutex_lock(&g_cursor_mtx);
//     render_a_tetromino_at(tetro, block_wprint, pos);
//     pthread_mutex_unlock(&g_cursor_mtx);
// }

static inline void render_a_tetromino_r(const tetromino_t* tetro, wchar_t block_wprint)
{
    debug();

    pthread_mutex_lock(&g_cursor_mtx);
    render_a_tetromino(tetro, block_wprint);
    pthread_mutex_unlock(&g_cursor_mtx);
    // render_a_tetromino_at_r(tetro, block_wprint, tetro->pos);
}

// static void erase_a_tetromino_at_r(const tetromino_t* tetro, pos_t pos)
// {
//     debug();

//     render_a_tetromino_at_r(tetro, BLOCK_WPRINT_WHITE_LARGE_SQUARE, pos);
// }

// static void draw_a_tetromino_at_r(const tetromino_t* tetro, pos_t pos)
// {
//     debug();

//     render_a_tetromino_at_r(tetro, tetro->block_code, pos);
// }

void erase_a_tetromino_r(const tetromino_t* tetro)
{
    debug();

    render_a_tetromino_r(tetro, BLOCK_WPRINT_WHITE_LARGE_SQUARE);
}

void draw_a_tetromino_r(const tetromino_t* tetro)
{
    debug();

    render_a_tetromino_r(tetro, tetro->block_code);
}

void render_out(void)
{
    debug();

    fflush(stdout);
}