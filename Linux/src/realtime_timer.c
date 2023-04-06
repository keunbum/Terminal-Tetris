#include "realtime_timer.h"
#include "debug.h"
#include "error_handling.h"

// void* run_realtime_timer(void* arg)
// {
//     debug();

//     realtime_timer_t* timer = (realtime_timer_t*) arg;

//     /* Set sigset */
//     sigemptyset(&timer->sigset);
//     sigaddset(&timer->sigset, timer->timersig);

//     /* Create timer */
//     sigevent_t sev;
//     sev.sigev_notify = SIGEV_SIGNAL;
//     sev.sigev_signo = timer->timersig;
//     sev.sigev_value.sival_int = 0;
//     sev._sigev_un._sigev_thread._function = NULL;
//     if (timer_create(timer->clockid, &sev, &timer->timerid) == -1) {
//         handle_error("timer_create() error");
//     }

//     /* Start timer */
//     if (timer_settime(timer->timerid, 0, &timer->its, NULL) == -1) {
//         handle_error("timer_settime() error");
//     }

//     /* Run main logic */
//     set_realtime_timer(timer, true);
//     timer->logic(timer->logic_arg);

//     /* Delete timer */
//     if (timer_delete(timer->timerid) == -1) {
//         handle_error("timer_delete() error");
//     }
//     ewprintf("run_timer_drawer_with() return NULL\n");
//     return NULL;
// }