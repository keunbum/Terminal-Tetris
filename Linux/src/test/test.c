#include <stdbool.h>
#include <unistd.h>

#include "test/test.h"

#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include <signal.h>
#include <time.h>


//Simple print information, timer trigger function
void print_info(int signo){
    printf("timer fired\n");
}

void init_sigaction(){
    struct sigaction act;
    act.sa_handler = print_info;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    sigaction(SIGPROF,&act,NULL); //Set the processing function of signal SIGPROF to print_info

}


void init_time() {
    struct itimerval value;
    value.it_value.tv_sec=2; //After the timer is started, the corresponding function will be executed every 2 seconds
    value.it_value.tv_usec=0;
    value.it_interval=value.it_value;
    setitimer(ITIMER_PROF,&value,NULL); //Initialize timer and send SIGPROF signal when it expires
}

int test_module(int argc, char* argv[])
{
    init_sigaction();
    init_time();
    while(1);

    return 0;
}