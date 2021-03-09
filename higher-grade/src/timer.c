//#pragma once
#include <stdlib.h>   // exit(), EXIT_FAILURE, EXIT_SUCCESS
#include <signal.h>   // sigaction()
#include <stdio.h>    // printf(), fprintf(), stdout, stderr, perror(), _IOLBF
#include <string.h>   // memset()
#include <sys/time.h> // ITIMER_REAL, ITIMER_VIRTUAL, ITIMER_PROF, struct itimerval, setitimer()
#include <stdbool.h>  // true, false 
#include <limits.h>   // INT_MAX
#include "sthreads.h"

#define TIMEOUT    100          // ms 
#define TIMER_TYPE ITIMER_REAL // Type of timer.

static volatile int foo;

void side_effect() {
  foo = (foo*foo) % 100;
}

/* The three types of timers causes different signals.

   type: type of timer, one of ITIMER_REAL, ITIMER_VIRTUAL, or ITIMER_PROF.

   return value: the signal generated by the timer.

 */
int timer_signal(int timer_type) {
  int sig;

  switch (timer_type) {
    case ITIMER_REAL:
      yield();
      sig = SIGALRM;
      break;
/*    case ITIMER_VIRTUAL:
      sig = SIGVTALRM;
      break;
    case ITIMER_PROF:
      sig = SIGPROF;
      break;
*/      
    default:
      fprintf(stderr, "ERROR: unknown timer type %d!\n", timer_type);
      exit(EXIT_FAILURE);
  }

  return sig;
}


/* Set a timer and a handler for the timer.
   Arguments
   type: type of timer, one of ITIMER_REAL, ITIMER_VIRTUAL, or ITIMER_PROF.
   handler: timer signal handler.
   ms: time in ms for the timer. 
 */
void set_timer(int type, void (*handler) (int), int ms) {
  struct itimerval timer;
  struct sigaction sa;

  /* Install signal handler for the timer. */
  memset(&sa, 0, sizeof (sa));
  sa.sa_handler =  handler;
  sigaction(timer_signal(type), &sa, NULL);

  /* Configure the timer to expire after ms msec... */
  timer.it_value.tv_sec = 1;
  timer.it_value.tv_usec = ms*1000;
  timer.it_interval.tv_sec = 0;
  timer.it_interval.tv_usec = 0;

  if (setitimer (type, &timer, NULL) < 0) {
    perror("Setting timer");
    exit(EXIT_FAILURE);
  };
}

/* Timer signal handler. */
void timer_handler (int signum) {
  static int count = 0;
  fprintf (stderr, "======> timer (%03d)\n", count++);
  set_timer(TIMER_TYPE, timer_handler, TIMEOUT);
}

/*
int main () {
  // Flush each printf() as it happens.
  setvbuf(stdout, 0, _IOLBF, 0);
  setvbuf(stderr, 0, _IOLBF, 0);

  set_timer(TIMER_TYPE, timer_handler, TIMEOUT);

  fibonacci_slow();
}
*/