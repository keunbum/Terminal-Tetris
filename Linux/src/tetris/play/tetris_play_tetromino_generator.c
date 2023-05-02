#include <stdlib.h>

#include "algorithm.h"
#include "debug.h"
#include "mt19937.h"
#include "tetris/object/block_wprint.h"
#include "tetris_play_tetromino_generator.h"
#include "tetris_play_tetromino_statistic.h"

static const block_wprint_set_t GS_BLOCK_WPRINT_SET_RAINBOW = {
    7,
    {
        L'\U0001f9ca', // skyblue
        // L'\U0001f7eb', // brown
        L'\U0001f7e8', // yellow
        L'\U0001f7ea', // purple
        L'\U0001f7e6', // blue
        L'\U0001f7e7', // orange
        L'\U0001f7e9', // green
        L'\U0001f7e5', // red
    },
};

// static const block_wprint_set_t GS_BLOCK_WPRINT_SET_EMOJI = {
//     7,
//     {
//         L'\U0001f301', // 🌁
//         L'\U0001f304', // 🌄
//         L'\U0001f386', // 🎆
//         L'\U0001f30c', // 🌌
//         L'\U0001f9f1', // 🧱
//         L'\U0001f4b9', // 💹
//         L'\U0001f9e7', // 🧧
//     },
// };

static const block_wprint_set_t* GS_BLOCK_WPRINT_SET = &GS_BLOCK_WPRINT_SET_RAINBOW;

void init_tetromino_generator(tetromino_generator_t* const out_gen)
{
    debug();

    my_assert(out_gen != NULL);

    out_gen->spawnd_cnt = 0;
    out_gen->block_wprint_set = GS_BLOCK_WPRINT_SET;
    out_gen->ptr = 0;
    iota_int(out_gen->symbols, out_gen->symbols + TETROMINO_NUM_OF_KINDS, 0);
}

void cleanup_tetromino_generator(tetromino_generator_t* const out_gen)
{
    debug();

    my_assert(out_gen != NULL);

    /* Do Nothing */
    (void)out_gen;
}

static inline symbol_id_t get_symbol_id_random_default(void)
{
    return (symbol_id_t)(rng() % TETROMINO_NUM_OF_KINDS);
}

static inline symbol_id_t get_symbol_id_random_7bag(tetromino_generator_t* const out_gen)
{
    if (out_gen->ptr == 0) {
        shuffle_int(out_gen->symbols, out_gen->symbols + TETROMINO_NUM_OF_KINDS);
    }
    symbol_id_t ret = out_gen->symbols[out_gen->ptr++];
    if (out_gen->ptr == TETROMINO_NUM_OF_KINDS) {
        out_gen->ptr = 0;
    }
    return ret;
}

tetromino_t* create_tetromino_random_malloc(tetromino_generator_t* const out_gen, pos_t init_pos, velocity_t init_velocity, block_wprint_t init_clean_block)
{
    debug();

    // symbol_id_t init_symbol_id = get_symbol_id_random_default();
    symbol_id_t init_symbol_id = get_symbol_id_random_7bag(out_gen);
    block_t init_block = { BLOCK_NATURE_FULL, GS_BLOCK_WPRINT_SET->wprint_values[init_symbol_id] };
    tetromino_t* pa_ret = init_tetromino_malloc(out_gen->spawnd_cnt++,
        init_symbol_id,
        TETROMINO_INIT_DIR,
        init_pos,
        init_velocity,
        init_block,
        init_clean_block,
        NULL);
    return pa_ret;
}

tetromino_t* create_tetromino_symbol_poswprint_malloc(tetromino_generator_t* const out_gen, symbol_id_t init_symbol_id, pos_t init_pos_wprint, block_wprint_t init_clean_block)
{
    debug();

    block_t init_block = { BLOCK_NATURE_FULL, GS_BLOCK_WPRINT_SET->wprint_values[init_symbol_id] };
    tetromino_t* pa_ret = init_tetromino_poswprint_malloc(out_gen->spawnd_cnt++,
        init_symbol_id,
        TETROMINO_INIT_DIR,
        init_pos_wprint,
        0,
        init_block,
        init_clean_block,
        NULL);
    return pa_ret;
}