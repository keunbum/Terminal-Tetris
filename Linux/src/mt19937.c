/* Ref:
 * Mersenne Twister: A 623-Dimensionally Equidistributed Uniform Pseudo-Random Number Generator
 * MAKOTO MATSUMOTO
 * Keio University and the Max-Planck-Institut fu¨ r Mathematik
 * and
 * TAKUJI NISHIMURA
 * Keio University
 */

#include <stdio.h>

#include "debug.h"
#include "mt19937.h"

#define W (32)
#define N (624)
#define M (397)
#define R (31)
#define MATRIX_A (0x9908B0DF) /* constant vector a */
#define LOWER_MASK ((1u << R) - 1)/* most significant w-r bits */
#define UPPER_MASK (~LOWER_MASK) /* least significant r bits */
/* Tempering parameters */
#define TEMPERING_MASK_B (0x9D2C5680)
#define TEMPERING_MASK_C (0xEFC60000)
#define F (1812433253)
#define TEMPERING_SHIFT_U(y) (y >> 11)
#define TEMPERING_SHIFT_S(y) (y << 7)
#define TEMPERING_SHIFT_T(y) (y << 15)
#define TEMPERING_SHIFT_L(y) (y >> 18)

static uint32_t mt[N]; /* the array for the state vector */
static size_t mti = N + 1;

/* initializing the array with a NONZERO seed */
void mt19937_srand(uint32_t seed)
{
    /* setting initial seeds to mt[N] using */
    mt[0] = seed;
    for (mti = 1; mti < N; ++mti) {
       mt[mti] = F * (mt[mti - 1] ^ (mt[mti - 1] >> (W - 2))) + mti;
    }
}

uint32_t mt19937_rng(void)
{
    uint32_t y;
    if (mti >= N) {
        static uint32_t mag01[2] = { 0x0, MATRIX_A };
        size_t kk;
        my_assert(mti != N + 1);
        for (kk = 0; kk < N - M; ++kk) {
            y = (mt[kk] & UPPER_MASK) | (mt[kk + 1] & LOWER_MASK);
            mt[kk] = mt[kk + M] ^ (y >> 1) ^ mag01[y & 0x1];
        }
        for (; kk < N - 1; ++kk) {
            y = (mt[kk] & UPPER_MASK) | (mt[kk + 1] & LOWER_MASK);
            mt[kk] = mt[kk + (M - N)] ^ (y >> 1) ^ mag01[y & 0x1];
        }
        y = (mt[N - 1] & UPPER_MASK) | (mt[0] & LOWER_MASK);
        mt[N - 1] = mt[M - 1] ^ (y >> 1) ^ mag01[y & 0x1];
        mti = 0;
    }
    y = mt[mti++];
    y ^= TEMPERING_SHIFT_U(y);
    y ^= TEMPERING_SHIFT_S(y) & TEMPERING_MASK_B;
    y ^= TEMPERING_SHIFT_T(y) & TEMPERING_MASK_C;
    y ^= TEMPERING_SHIFT_L(y);
    return y;
}