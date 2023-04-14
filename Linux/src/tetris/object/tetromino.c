#include <time.h>

#include "debug.h"
#include "tetromino.h"

/* Should I just unify it to 4? */
const tetromino_matrix_n_t G_TETROMINO_MATRIX_NS[TOTAL_TETROMINO_NUM_OF_KINDS] = {
    4, 2, 3, 3, 3, 3, 3
};

const tetromino_matrix_t G_TETROMINO_MATRIXS[TOTAL_TETROMINO_NUM_OF_KINDS][TOTAL_DIR_NUM_OF_KINDS] = {
    { 0x00F0, 0x2222, 0x0F00, 0x4444 }, // I
    { 0x000F, 0x000F, 0x000F, 0x000F }, // O
    { 0x003A, 0x009A, 0x00B8, 0x00B2 }, // T
    { 0x01C8, 0x01A4, 0x0027, 0x004B }, // J
    { 0x01E0, 0x0126, 0x000F, 0x00C9 }, // L
    { 0x00F0, 0x0132, 0x001E, 0x0099 }, // S
    { 0x0198, 0x00B4, 0x0033, 0x005A }, // Z
};

tetromino_lock_t g_tetromino_lock;
