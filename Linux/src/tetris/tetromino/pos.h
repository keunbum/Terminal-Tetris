#ifndef __POS__H
#define __POS__H

#define DECLARE_POS_T(T) \
    typedef struct {     \
        T x;             \
        T y;             \
    } pos_t

DECLARE_POS_T(int);

#endif /* __POS__H */