#include "block.h"
#include "debug/debug.h"
#include "game/game_play/random/random.h"

const block_code_set_t G_BLOCK_CODE_SET_RAINBOW = {
    .size = 7,
    .codes = {
        L'\U0001f7e5', // red
        L'\U0001f7e7', // orange
        L'\U0001f7e8', // yellow
        L'\U0001f7e9', // green
        L'\U0001f7e6', // blue
        L'\U0001f7ea', // purple
        L'\U0001f7eb', // brown
    },
};

const block_code_set_t G_BLOCK_CODE_SET_DEFAULT = {
    .size = 7,
    .codes = {
        L'\U0001f7e5', // red
        L'\U0001f7e7', // orange
        L'\U0001f7e8', // yellow
        L'\U0001f7e9', // green
        L'\U0001f7e6', // blue
        L'\U0001f7ea', // purple
        L'\U0001f7eb', // brown
    },
};

int get_block_code_random(const block_code_set_t* bs)
{
    debug();

    int ret = (int)(rng() % bs->size);
    my_assert(ret >= 0);
    return ret;
}

int get_block_code_fixed(const block_code_set_t* bs, int symbol_id, int rotation)
{
    debug();
    int ret = (int) ((symbol_id + rotation) % bs->size);
    my_assert(ret >= 0);
    return ret;
}