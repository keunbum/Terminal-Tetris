#include <stdlib.h>
#include <time.h>

#include "debug.h"
#include "tetromino.h"

const tetromino_shape_t G_TETROMINO_SYMBOLS[TETROMINO_NUM_OF_KINDS][DIR_NUM_OF_KINDS] = {
    { 0x00F0, 0x4444, 0x0F00, 0x2222 }, // I
    { 0x0660, 0x0660, 0x0660, 0x0660 }, // O
    { 0x0072, 0x0262, 0x0270, 0x0232 }, // T
    { 0x0071, 0x0226, 0x0470, 0x0322 }, // J
    { 0x0074, 0x0622, 0x0170, 0x0223 }, // L
    { 0x0036, 0x0462, 0x0360, 0x0231 }, // S
    { 0x0063, 0x0264, 0x0630, 0x0132 }, // Z
};

static void init_tetromino(tetromino_t* const out_tetro, shape_id_t shape_id, dir_t dir, pos_t pos, pos_t pos_wprint, velocity_t velocity, block_t block, block_wprint_t clean_wprint, tetromino_t* prev_drawn)
{
    out_tetro->shape_id = shape_id;
    out_tetro->dir = dir;
    out_tetro->pos = pos;
    out_tetro->pos_wprint = pos_wprint;
    out_tetro->velocity = velocity;
    out_tetro->block = block;
    out_tetro->clean_wprint = clean_wprint;
    out_tetro->prev_drawn = prev_drawn;
}

const wchar_t* get_dir_wstr(dir_t dir)
{
    static const wchar_t* S_STRS[DIR_NUM_OF_KINDS] = { L"DIR_BOT", L"DIR_RIGHT", L"DIR_TOP", L"DIR_LEFT" };
    return S_STRS[dir];
}

wchar_t get_shape_wch(shape_id_t shape_id)
{
    static const wchar_t S_ID2SYMBOL[TETROMINO_NUM_OF_KINDS] = { L'I', L'O', L'T', L'J', L'L', L'S', L'Z' };
    return S_ID2SYMBOL[shape_id];
}

void save_tetromino_tobedrawn(tetromino_t* const out_tetro)
{
    my_assert(is_valid_tetromino(out_tetro));

    if (!is_valid_tetromino(out_tetro->prev_drawn)) {
        out_tetro->prev_drawn = (tetromino_t*)malloc(sizeof(tetromino_t));
    }
    out_tetro->prev_drawn->shape_id = out_tetro->shape_id;
    out_tetro->prev_drawn->dir = out_tetro->dir;
    out_tetro->prev_drawn->pos = out_tetro->pos;
    out_tetro->prev_drawn->pos_wprint = out_tetro->pos_wprint;
    out_tetro->prev_drawn->block = create_block(BLOCK_NATURE_EMPTY, out_tetro->clean_wprint);
}

void cleanup_tetromino_free(tetromino_t* const out_tetro)
{
    if (out_tetro == NULL) {
        return;
    }
    if (out_tetro->prev_drawn != NULL) {
        free(out_tetro->prev_drawn);
        out_tetro->prev_drawn = NULL;
    }
    free(out_tetro);
}

tetromino_t* init_tetromino_malloc(shape_id_t shape_id, dir_t dir, pos_t pos, velocity_t velocity, block_t block, block_wprint_t clean_wprint, tetromino_t* prev_drawn)
{
    tetromino_t* pa_tetro = (tetromino_t*)malloc(sizeof(tetromino_t));
    init_tetromino(pa_tetro, shape_id, dir, pos, create_pos_default(), velocity, block, clean_wprint, prev_drawn);
    return pa_tetro;
}

tetromino_t* init_tetromino_poswprint_malloc(shape_id_t shape_id, dir_t dir, pos_t pos_wprint, velocity_t velocity, block_t block, block_wprint_t clean_wprint, tetromino_t* prev_drawn)
{
    tetromino_t* pa_tetro = (tetromino_t*)malloc(sizeof(tetromino_t));
    init_tetromino(pa_tetro, shape_id, dir, create_pos_default(), pos_wprint, velocity, block, clean_wprint, prev_drawn);
    return pa_tetro;
}
