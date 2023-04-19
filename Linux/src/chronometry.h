#ifndef __CHRONOMETRY__H
#define __CHRONOMETRY__H

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <assert.h>

typedef float __sseconds_t;
typedef __syscall_slong_t __snseconds_t;

#define NSEC_VAL ((__snseconds_t)1e9)

#define TO_NSEC(sec) ((__snseconds_t)(NSEC_VAL * (sec)))
#define TO_SEC(nsec) ((__sseconds_t)nsec / NSEC_VAL)

#define get_chrono_time(spec_ptr) clock_gettime(CLOCK_REALTIME, spec_ptr)

static inline struct timespec nsec_to_timespec(__snseconds_t nsec)
{
    struct timespec ret = { nsec / NSEC_VAL, nsec % NSEC_VAL };
    return ret;
}

static inline struct timespec sec_to_timespec(__sseconds_t sec)
{
    return nsec_to_timespec(TO_NSEC(sec));
}

static inline struct timespec timespec_diff(const struct timespec* restrict start, const struct timespec* restrict end)
{
    __snseconds_t nsec = TO_NSEC(end->tv_sec - start->tv_sec) + (end->tv_nsec - start->tv_nsec);
    assert(nsec >= 0);
    return nsec_to_timespec(nsec);
}

static inline struct timespec get_elapsed_time(const struct timespec* start)
{
    struct timespec end;
    get_chrono_time(&end);
    struct timespec ret = timespec_diff(start, &end);
    return ret;
}

static inline __snseconds_t timespec_to_nsec(struct timespec ts)
{
    return TO_NSEC(ts.tv_sec) + ts.tv_nsec;
}

static inline __sseconds_t timespec_to_sec(struct timespec ts)
{
    return (__sseconds_t)ts.tv_sec + TO_SEC(ts.tv_nsec);
}

static inline __snseconds_t get_elapsed_time_nsec(const struct timespec* start)
{
    return timespec_to_nsec(get_elapsed_time(start));
}

static inline __sseconds_t get_elapsed_time_sec(const struct timespec* start)
{
    return timespec_to_sec(get_elapsed_time(start));
}

static inline void nanosleep_chrono(__snseconds_t nsec)
{
    struct timespec ts = nsec_to_timespec(nsec);
    nanosleep(&ts, NULL);
}

#endif /* __CHRONOMETRY__H */