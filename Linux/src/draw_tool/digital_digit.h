#ifndef __DIGITAL_DIGIT__H
#define __DIGITAL_DIGIT__H

#include <wchar.h>

#define DIGITAL_DIGIT_HEIGHT (5)
#define DIGITAL_DIGIT_WIDTH (5)

typedef wchar_t* digital_digit_t[DIGITAL_DIGIT_HEIGHT];
//typedef char* digital_digit_t[DIGITAL_DIGIT_HEIGHT];

extern const digital_digit_t G_DIGITAL_DIGITS[];
extern const digital_digit_t G_DIGITAL_DIGIT_EMPTY;

void wdraw_digital_digit_at_r(const digital_digit_t, int, int);

#endif /* __DIGITAL_DIGIT__H */