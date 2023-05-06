#include <stdlib.h>

#include "algorithm.h"
#include "debug.h"
#include "mt19937.h"
#include "tetris/object/block_wprint.h"
#include "tetris_play_tetromino_generator.h"
#include "tetris_play_tetromino_statistic.h"

static const block_wprint_set_t GS_BLOCK_WPRINT_SET_RAINBOW = {
    .size = 7,
    .wprint_values = {
        L'\U0001f9ca', // cyan (Since there is no cyan block, I replaced it with another emoji T-T..)
        L'\U0001f7e8', // yellow
        L'\U0001f7ea', // purple
        L'\U0001f7e6', // blue
        L'\U0001f7e7', // orange
        L'\U0001f7e9', // green
        L'\U0001f7e5', // red
    },
};
static const block_wprint_set_t* GS_BLOCK_WPRINT_SET_DEFAULT = &GS_BLOCK_WPRINT_SET_RAINBOW;

void init_tetromino_generator(tetromino_generator_t* const out_gen)
{
    out_gen->tetromino_spawnd_cnt = 0;
    out_gen->block_wprint_set = GS_BLOCK_WPRINT_SET_DEFAULT;
    out_gen->symbols_ptr = 0;
    iota_int(out_gen->symbols, out_gen->symbols + TETROMINO_NUM_OF_KINDS, 0);
    shuffle_int(out_gen->symbols, out_gen->symbols + TETROMINO_NUM_OF_KINDS);
}

void cleanup_tetromino_generator(tetromino_generator_t* const out_gen)
{
    /* Do Nothing */
    (void)out_gen;
}

static inline symbol_id_t get_symbol_id_random_7bag(tetromino_generator_t* const out_gen)
{
    symbol_id_t ret = out_gen->symbols[out_gen->symbols_ptr++];
    if (out_gen->symbols_ptr == TETROMINO_NUM_OF_KINDS) {
        out_gen->symbols_ptr = 0;
        shuffle_int(out_gen->symbols, out_gen->symbols + TETROMINO_NUM_OF_KINDS);
    }
    return ret;
}

tetromino_t* create_tetromino_random_malloc(tetromino_generator_t* const out_gen, pos_t init_pos, velocity_t init_velocity, block_wprint_t init_clean_block)
{
    symbol_id_t init_symbol_id = get_symbol_id_random_7bag(out_gen);
    block_t init_block = { BLOCK_NATURE_FULL, GS_BLOCK_WPRINT_SET_DEFAULT->wprint_values[init_symbol_id] };
    return init_tetromino_malloc(
        init_symbol_id,
        TETROMINO_INIT_DIR,
        init_pos,
        init_velocity,
        init_block,
        init_clean_block,
        NULL);
}

tetromino_t* create_tetromino_symbol_poswprint_malloc(symbol_id_t init_symbol_id, pos_t init_pos_wprint, block_wprint_t init_clean_block)
{
    block_t init_block = { BLOCK_NATURE_FULL, GS_BLOCK_WPRINT_SET_DEFAULT->wprint_values[init_symbol_id] };
    return init_tetromino_poswprint_malloc(
        init_symbol_id,
        TETROMINO_INIT_DIR,
        init_pos_wprint,
        0,
        init_block,
        init_clean_block,
        NULL);
}