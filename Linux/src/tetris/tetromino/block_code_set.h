#ifndef __BLOCK_CODE_SET__H
#define __BLOCK_CODE_SET__H

#include "block.h"

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

typedef wchar_t block_code_t;

typedef struct {
    const int size;
    const block_code_t codes[];
} block_code_set_t;

extern const block_code_set_t* G_BLOCK_CODE_SET;

// int get_block_code_random(const block_code_set_t*);
int get_block_code_fixed(int, int);

#endif /* __BLOCK_CODE_SET__H */
