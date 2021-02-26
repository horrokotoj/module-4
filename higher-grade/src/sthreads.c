/* On Mac OS (aka OS X) the ucontext.h functions are deprecated and requires the
   following define.
*/
#define _XOPEN_SOURCE 700

/* On Mac OS when compiling with gcc (clang) the -Wno-deprecated-declarations
   flag must also be used to suppress compiler warnings.
*/

#include <signal.h>   /* SIGSTKSZ (default stack size), MINDIGSTKSZ (minimal
                         stack size) */
#include <stdio.h>    /* puts(), printf(), fprintf(), perror(), setvbuf(), _IOLBF,
                         stdout, stderr */
#include <stdlib.h>   /* exit(), EXIT_SUCCESS, EXIT_FAILURE, malloc(), free() */
#include <ucontext.h> /* ucontext_t, getcontext(), makecontext(),
                         setcontext(), swapcontext() */
#include <stdbool.h>  /* true, false */

#include "sthreads.h"

/* Stack size for each context. */
#define STACK_SIZE SIGSTKSZ*100

/*******************************************************************************
                             Global data structures

                Add data structures to manage the threads here.
********************************************************************************/

//
struct thread_mangager {
  thread_t *first_ready;
  thread_t *last_ready;
  thread_t *first_waiting;
  thread_t *last_waiting;
  thread_t *first_terminated;
  thread_t *last_terminated;
  size_t size;
  size_t id_counter;
  
};

typedef struct thread_mangager thread_manager_t;


/*******************************************************************************
                             Auxiliary functions

                      Add internal helper functions here.
********************************************************************************/




/*******************************************************************************
                    Implementation of the Simple Threads API
********************************************************************************/

/*
  TODO: remove when done implementing
  Initialization of global thread management data structures. A user program
  must call this function exactly once before calling any other functions in
  the Simple Threads API.
*/

int  init(){
  thread_manager_t *manager = calloc(1, sizeof(thread_manager_t));
  manager->first_ready = NULL;
  manager->last_ready = NULL;
  manager->first_waiting = NULL;
  manager->last_waiting = NULL;
  manager->first_terminated = NULL;
  manager->last_terminated = NULL;
  manager->size = 0;
  manager->id_counter = 0;
  // if (success)
  return 1;
  //else return -1
}




/* Creates a new thread executing the start function.

   start - a function with zero arguments returning void.

   On success the positive thread ID of the new thread is returned. On failure a
   negative value is returned.
*/
tid_t spawn(void (*start)()){
  thread_t *thread = calloc(1, sizeof(thread_t));
  if (thread == NULL) return -1;
  
  thread->tid = tid;
  thread->state = ready;
  thread->next = NULL;

  if (getcontext(&thread->ctx) == -1) {
    free(thread);
    return -1;
  }
  return -1;
}




/* Cooperative scheduling

   If there are other threads in the ready state, a thread calling yield() will
   trigger the thread scheduler to dispatch one of the threads in the ready
   state and change the state of the calling thread from running to ready.
*/
void yield(){
}







/* Thread termination

   A thread calling done() will change state from running to terminated. If
   there are other threads waiting to join, these threads will change state from
   waiting to ready. Next, the thread scheduler will dispatch one of the ready
   threads.
*/
void  done(){
}





/* Join with a terminated thread

   The join() function waits for the specified thread to terminate.
   If the specified thread has already terminated, join() should return immediately.

   A thread calling join(thread) will be suspended and change state from running to
   waiting and trigger the thread scheduler to dispatch one of the ready
   threads. The suspended thread will change state from waiting to ready once the thread with
   thread id thread calls done and join() should then return the thread id of the
   terminated thread.
*/
tid_t join() {
  return -1;
}
