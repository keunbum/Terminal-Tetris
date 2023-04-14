#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#include "chronometry.h"

int test_chronometry()
{
    struct timespec total_start;
    get_chrono_time(&total_start);
    for (int i = 0; i < 60; ++i) {
        struct timespec start;
        get_chrono_time(&start);
        printf("cur time: %lf\n", get_elapsed_time_sec(&total_start));
        nanosleep_chrono(TO_NSEC(1.0 / 60) - get_elapsed_time_nsec(&start));
    }

    return 0;
}