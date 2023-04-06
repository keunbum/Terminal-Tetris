#ifndef __POS__H
#define __POS__H

#define DECLARE_POS_T(T) \
    typedef struct {     \
        T x;             \
        T y;             \
    } pos_##T##_t

//DECLARE_POS_T(double);
DECLARE_POS_T(int);

typedef pos_int_t pos_t;

#endif /* __POS__H */