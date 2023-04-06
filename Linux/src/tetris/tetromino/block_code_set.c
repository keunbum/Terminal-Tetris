#include "block_code_set.h"
#include "debug.h"
#include "random.h"
#include "tetris/tetromino/tetromino.h"

/* normal order
 1. I
 2. O
 3. T
 4. J
 5. L
 6. S
 7. Z
 */

/* <useful emojis>
 * L'\U0001f338', // 🌸
 * L'\U0001f5ff', // 🗿
 * L'\U0001f315', // 🌕
 * L'\U0001f386', // 🎆
 * L'\U0001f3b2', // 🎲
 * L'\U0001f4c1', // 📁
 * L'\U0001f9ca', // 🧊
 * L'\U0001f4f3', // 📳
 * L'\U0001f4d4', // 📔
 * L'\U0001f9e0', // 🧠
 * L'\U0001f303', // 🌃
 * L'\U0001f3ae', // 🎮
 * L'\u274E', // ❎
 * L'\U0001f381', // 🎁
 * L'\U0001f991', // 🦑
 * L'\U0001f504', // 🔄
 * L'\U0001f4c9', // 📉
 * L'\U0001f3fb', // 🏻
 * L\U0001f3fc', // 🏼
 */

const block_code_set_t G_BLOCK_CODE_SET_RAINBOW = {
    7,
    {
        L'\U0001f7eb', // brown
        L'\U0001f7e8', // yellow
        L'\U0001f7ea', // purple
        L'\U0001f7e7', // orange
        L'\U0001f7e6', // blue
        L'\U0001f7e9', // green
        L'\U0001f7e5', // red
    },
};

const block_code_set_t G_BLOCK_CODE_SET_EMOJI = {
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

const block_code_set_t* G_BLOCK_CODE_SET = &G_BLOCK_CODE_SET_EMOJI;

int get_block_code_random(const block_code_set_t* bcs)
{
    debug();

    int ret = (int)(rng() % bcs->size);
    my_assert(ret >= 0);
    return ret;
}

int get_block_code_fixed(int pos, int size)
{
    debug();

    int ret = pos % size;
    my_assert(ret >= 0);
    return ret;
}