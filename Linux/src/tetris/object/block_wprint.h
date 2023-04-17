#ifndef __BLOCK_CODE__H
#define __BLOCK_CODE__H

#include <wchar.h>

#include "debug.h"

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

// ref: https://ko.wikipedia.org/wiki/%ED%8B%80:%EC%9D%B4%EB%AA%A8%EC%A7%80_(%EC%9C%A0%EB%8B%88%EC%BD%94%EB%93%9C_%EB%B8%94%EB%A1%9D)
// ref: https://en.wikipedia.org/wiki/Geometric_Shapes_(Unicode_block)
// ref: https://en.wikipedia.org/wiki/Box-drawing_character
// ref: https://www.compart.com/en/unicode/block/U+25A0

typedef enum {
    BLOCK_WPRINT_EMPTY = (int)(L' '),
    BLOCK_WPRINT_BLACK_LARGE_SQUARE = (int)(0x2B1B),
    BLOCK_WPRINT_WHITE_LARGE_SQUARE = (int)(0x2B1C),
    BLOCK_WPRINT_BLACK_SQUARE_BUTTON = (int)(L'\U0001f532'),
    BLOCK_WPRINT_LIGHT_LARGE_SQUARE = (int)(L'\U0001f3fb'),
    BLOCK_WPRINT_SKYLINE = (int)(L'\u274E'),
    BLOCK_WPRINT_NIGHTSKY = (int)(L'\U0001f386'),
} block_wprint_t;

#endif /* __BLOCK_CODE__H */
