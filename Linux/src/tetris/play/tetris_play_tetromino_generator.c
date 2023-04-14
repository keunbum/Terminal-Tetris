#include "tetris_play_tetromino_generator.h"
#include "debug.h"
#include "mt19937.h"
#include "tetris/object/block_code.h"
#include "tetris_play_statistic.h"

static tetromino_id_t g_s_tetromino_spawned_cnt;

void init_tetromino_generator(void)
{
    debug();

    g_s_tetromino_spawned_cnt = 1;
}

// void spawn_tetromino(tetromino_t* restrict const out_tetro, pos_t init_pos, velocity_t init_velocity)
// {
//     debug();

//     out_tetro->id = g_s_tetromino_spawned_cnt++;
//     out_tetro->symbol_id = (symbol_id_t)(rng() % TOTAL_TETROMINO_NUM_OF_KINDS);
//     out_tetro->pos = init_pos;
//     out_tetro->velocity = init_velocity;
//     out_tetro->dir = DIR_BOT;
//     out_tetro->block_code = G_BLOCK_CODE_SET->codes[get_block_code_fixed(out_tetro->symbol_id, G_BLOCK_CODE_SET->size)];

//     inc_tetromino_cnt_by_one(out_tetro->symbol_id);
// }

void new_spawn_tetromino(tetris_play_manager_t* const restrict play_manager, tetromino_t* const restrict out_tetro, pos_t init_pos, velocity_t init_velocity)
{
    debug();

    out_tetro->id = g_s_tetromino_spawned_cnt++;
    out_tetro->symbol_id = (symbol_id_t)(rng() % TOTAL_TETROMINO_NUM_OF_KINDS);
    out_tetro->pos = init_pos;
    out_tetro->velocity = init_velocity;
    out_tetro->dir = DIR_BOT;
    out_tetro->block_code = G_BLOCK_CODE_SET->codes[out_tetro->symbol_id];

    new_inc_tetromino_cnt_by_one(&play_manager->statistics, out_tetro->symbol_id);
}
