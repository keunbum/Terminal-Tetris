#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

double time_diff(struct timeval* start, struct timeval* end)
{
    return (end->tv_sec - start->tv_sec) + 1e-6 * (end->tv_usec - start->tv_usec);
}

int test_gettimeofday()
{

    struct timeval start;
    gettimeofday(&start, NULL);
    for (int i = 0; i < 60; ++i) {
        struct timeval cur;
        gettimeofday(&cur, NULL);
        printf("cur time: %lf\n", time_diff(&start, &cur));
        usleep(16667);
    }

    return 0;
}