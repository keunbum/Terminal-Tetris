#ifndef __POLYOMINO__H
#define __POLYOMINO__H

#define DECLARE_POLYOMINO_SYMBOL_T(T) \
    typedef struct {                  \
        int height;                   \
        block_t* block_matrix[T];     \
    } polyomino_symbol_##T##_t

#endif /* __POLYOMINO__H */