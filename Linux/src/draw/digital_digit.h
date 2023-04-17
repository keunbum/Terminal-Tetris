#ifndef __DIGITAL_DIGIT__H
#define __DIGITAL_DIGIT__H

#include <wchar.h>

#define DIGITAL_DIGIT5_HEIGHT (5)
#define DIGITAL_DIGIT5_WIDTH (5)
typedef wchar_t* digital_digit5_t[DIGITAL_DIGIT5_HEIGHT];

extern const digital_digit5_t G_DIGITAL_DIGIT5S[];
extern const digital_digit5_t G_DIGITAL_DIGIT5_EMPTY;

void wdraw_digital_digit5_at_r(const digital_digit5_t, int, int);

#endif /* __DIGITAL_DIGIT__H */