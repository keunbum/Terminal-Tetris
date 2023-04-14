#include "tetris_play_tetromino_generator.h"
#include "debug.h"
#include "mt19937.h"
#include "tetris/object/block_wprint.h"
#include "tetris_play_statistic.h"

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

    out_gen->tetromino_spawned_cnt = 0;
    out_gen->block_wprint_set = G_S_BLOCK_WPRINT_SET;
}

void spawn_tetromino(tetromino_generator_t* const restrict out_gen, tetromino_t* const restrict out_tetro, pos_t init_pos, velocity_t init_velocity)
{
    debug();

    out_tetro->id = out_gen->tetromino_spawned_cnt++;
    out_tetro->symbol_id = (symbol_id_t)(rng() % TOTAL_TETROMINO_NUM_OF_KINDS);
    out_tetro->pos = init_pos;
    out_tetro->velocity = init_velocity;
    out_tetro->dir = TETROMINO_INIT_DIR;
    out_tetro->block.nature = BLOCK_NATURE_FULL;
    out_tetro->block.wprint = G_S_BLOCK_WPRINT_SET->wprint_values[out_tetro->symbol_id];
}
