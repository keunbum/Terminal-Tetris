#ifndef __BLOCK__H
#define __BLOCK__H

#include <wchar.h>

// ref: https://ko.wikipedia.org/wiki/%ED%8B%80:%EC%9D%B4%EB%AA%A8%EC%A7%80_(%EC%9C%A0%EB%8B%88%EC%BD%94%EB%93%9C_%EB%B8%94%EB%A1%9D)
// ref: https://en.wikipedia.org/wiki/Geometric_Shapes_(Unicode_block)
// ref: https://en.wikipedia.org/wiki/Box-drawing_character
// ref: https://www.compart.com/en/unicode/block/U+25A0
// ref: https://emojiterra.com/geometric-symbols/
#define BLOCK_BLACK_LARGE_SQUARE_WPRINT (0x2B1B)
#define BLOCK_WHITE_LARGE_SQUARE_WPRINT (0x2B1C)

typedef char block_t;

#define BLOCK_T_TRUE ('1')
#define BLOCK_T_FALSE ('0')

#endif /* __BLOCK__H */