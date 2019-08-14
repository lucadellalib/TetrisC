/**
 * @file timer.c
 * @brief Functions to create and handle a timer.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 *
 * @copyright Copyright © 2017 Luca Della Libera. All rights reserved.
 */

/**
 * @addtogroup Utils
 * @{
 */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>

#include "shared.h"
#include "timer.h"


static struct sigaction s_action; /**< @brief Structure to define the signal handler. */
static struct sigevent s_event; /**< @brief Structure to define the timer. */
static struct itimerspec it_spec; /**< @brief Structure to define timer tick interval. */
static timer_t timerID; /**< @brief Timer ID. */

void make_timer(void (*handler)()) {
    int sig_no = SIGRTMIN;
    // init structures for signal handler
    s_action.sa_flags = SA_SIGINFO;
    s_action.sa_sigaction = handler;
    sigemptyset(&s_action.sa_mask);

    // assign signal handler
    if (sigaction(sig_no, &s_action, NULL) == -1) {
        ERROR_EXIT("sigaction");
    }

    // init the structure for timer
    s_event.sigev_notify = SIGEV_SIGNAL;
    s_event.sigev_signo = sig_no;

    // assign timer
    if (timer_create(CLOCK_REALTIME, &s_event, &timerID) == -1) {
        ERROR_EXIT("timer_create");            
    }
}

void start_timer(int interval_millis) {
    // init the structure to define the timer tick interval
    it_spec.it_value.tv_sec = 0;
    it_spec.it_value.tv_nsec = interval_millis*1000000;
    it_spec.it_interval.tv_sec = 0;
    it_spec.it_interval.tv_nsec = interval_millis*1000000;

    // assign interval
    if (timer_settime(timerID, 0, &it_spec, NULL) == -1) {
        ERROR_EXIT("timer_settime");
    }
}

void stop_timer() {
    it_spec.it_value.tv_sec = 0;
    it_spec.it_value.tv_nsec = 0;
    it_spec.it_interval.tv_sec = 0;
    it_spec.it_interval.tv_nsec = 0;

    if (timer_settime(timerID, 0, &it_spec, NULL) == -1) {
        ERROR_EXIT("timer_settime");
    }
}

void delete_timer() {
   timer_delete(timerID);
}
/** \} */
