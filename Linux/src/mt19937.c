/* Ref: https://dl.acm.org/doi/pdf/10.1145/272991.272995
 *
 * Mersenne Twister: A 623-Dimensionally Equidistributed Uniform Pseudo-Random Number Generator
 * MAKOTO MATSUMOTO
 * Keio University and the Max-Planck-Institut fu¨ r Mathematik
 * and
 * TAKUJI NISHIMURA
 * Keio University
 * 
 */
#include <stddef.h>

#include "debug.h"
#include "mt19937.h"

#define W (32)
#define N (624)
#define M (397)
#define R (31)
#define MATRIX_A (0x9908B0DF) /* constant vector a */
#define LOWER_MASK ((1u << (R)) - 1) /* most significant w-r bits */
#define UPPER_MASK (~(LOWER_MASK)) /* least significant r bits */
/* Tempering parameters */
#define TEMPERING_MASK_B (0x9D2C5680)
#define TEMPERING_MASK_C (0xEFC60000)
#define F (1812433253)
#define TEMPERING_SHIFT_U(y) ((y) >> 11)
#define TEMPERING_SHIFT_S(y) ((y) << 7)
#define TEMPERING_SHIFT_T(y) ((y) << 15)
#define TEMPERING_SHIFT_L(y) ((y) >> 18)

static uint32_t s_mt[N]; /* the array for the state vector */
static size_t s_mti = N + 1;

/* initializing the array with a NONZERO seed */
void mt19937_srand(uint32_t seed)
{
    /* setting initial seeds to s_mt[N] */
    s_mt[0] = seed;
    for (s_mti = 1; s_mti < N; ++s_mti) {
        s_mt[s_mti] = F * (s_mt[s_mti - 1] ^ (s_mt[s_mti - 1] >> (W - 2))) + s_mti;
    }
}

uint32_t mt19937_rng(void)
{
    uint32_t y;
    if (s_mti >= N) {
        static uint32_t mag01[2] = { 0x0, MATRIX_A };
        size_t kk;
        for (kk = 0; kk < N - M; ++kk) {
            y = (s_mt[kk] & UPPER_MASK) | (s_mt[kk + 1] & LOWER_MASK);
            s_mt[kk] = s_mt[kk + M] ^ (y >> 1) ^ mag01[y & 0x1];
        }
        for (; kk < N - 1; ++kk) {
            y = (s_mt[kk] & UPPER_MASK) | (s_mt[kk + 1] & LOWER_MASK);
            s_mt[kk] = s_mt[kk + (M - N)] ^ (y >> 1) ^ mag01[y & 0x1];
        }
        y = (s_mt[N - 1] & UPPER_MASK) | (s_mt[0] & LOWER_MASK);
        s_mt[N - 1] = s_mt[M - 1] ^ (y >> 1) ^ mag01[y & 0x1];
        s_mti = 0;
    }
    y = s_mt[s_mti++];
    y ^= TEMPERING_SHIFT_U(y);
    y ^= TEMPERING_SHIFT_S(y) & TEMPERING_MASK_B;
    y ^= TEMPERING_SHIFT_T(y) & TEMPERING_MASK_C;
    y ^= TEMPERING_SHIFT_L(y);
    return y;
}
