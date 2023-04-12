#ifndef __CHRONOMETRY__H
#define __CHRONOMETRY__H

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

static inline double time_diff(struct timeval* start, struct timeval* end)
{
    return (double)(end->tv_sec - start->tv_sec) + 1e-6 * (end->tv_usec - start->tv_usec);
}

static inline __suseconds_t time_diff_usec(struct timeval* start, struct timeval* end)
{
    return ((__suseconds_t)1e6) * (__suseconds_t)(end->tv_sec - start->tv_sec) + (end->tv_usec - start->tv_usec);
}

static inline __suseconds_t get_curr_time_usec(struct timeval* start)
{
    struct timeval end;
    gettimeofday(&end, NULL);
    return time_diff_usec(start, &end);
}

static inline double get_curr_time(struct timeval* start)
{
    struct timeval end;
    gettimeofday(&end, NULL);
    return time_diff(start, &end);
}

#endif /* __CHRONOMETRY__H */