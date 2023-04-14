#ifndef __POS__H
#define __POS__H

#include <stdbool.h>

#define DECLARE_POS_T(T) \
    typedef struct {     \
        T x;             \
        T y;             \
    } pos_t

typedef double pos_e_t;

DECLARE_POS_T(pos_e_t);

#endif /* __POS__H */