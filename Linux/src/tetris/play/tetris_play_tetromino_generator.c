#include <stdlib.h>

#include "debug.h"
#include "mt19937.h"
#include "tetris/object/block_wprint.h"
#include "tetris_play_tetromino_generator.h"
#include "tetris_play_tetromino_statistic.h"

// static const block_wprint_set_t G_S_BLOCK_WPRINT_SET_RAINBOW = {
//     7,
//     {
//         L'\U0001f7eb', // brown
//         L'\U0001f7e8', // yellow
//         L'\U0001f7ea', // purple
//         L'\U0001f7e7', // orange
//         L'\U0001f7e6', // blue
//         L'\U0001f7e9', // green
//         L'\U0001f7e5', // red
//     },
// };

static const block_wprint_set_t G_S_BLOCK_WPRINT_SET_EMOJI = {
    7,
    {
        L'\U0001f301', // 🌁
        L'\U0001f304', // 🌄
        L'\U0001f386', // 🎆
        L'\U0001f30c', // 🌌
        L'\U0001f9f1', // 🧱
        L'\U0001f4b9', // 💹
        L'\U0001f9e7', // 🧧
    },
};

static const block_wprint_set_t* G_S_BLOCK_WPRINT_SET = &G_S_BLOCK_WPRINT_SET_EMOJI;

void init_tetromino_generator(tetromino_generator_t* const out_gen)
{
    debug();

    my_assert(out_gen != NULL);

    out_gen->block_wprint_set = G_S_BLOCK_WPRINT_SET;
}

tetromino_t* spawn_tetromino_malloc(pos_t init_pos, velocity_t init_velocity)
{
    debug();

    symbol_id_t init_symbol_id = (symbol_id_t)(rng() % TETROMINO_NUM_OF_KINDS);
    block_t init_block = { BLOCK_NATURE_FULL, G_S_BLOCK_WPRINT_SET->wprint_values[init_symbol_id] };
    tetromino_t* pa_ret = init_tetromino_malloc(
        init_symbol_id,
        init_pos,
        TETROMINO_INIT_DIR,
        init_velocity,
        init_block,
        NULL);
    return pa_ret;
}