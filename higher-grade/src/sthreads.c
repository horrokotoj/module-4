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
struct thread_manager {
  thread_t *first_ready;
  thread_t *last_ready;
  thread_t *first_waiting;
  thread_t *last_waiting;
  thread_t *first_terminated;
  thread_t *last_terminated;
  thread_t *running;
  size_t size_ready;
  size_t size_waiting;
  size_t size_terminated;
  size_t id_counter;
  
};

typedef struct thread_manager thread_manager_t;

thread_manager_t *manager = NULL;


/*******************************************************************************
                             Auxiliary functions

                      Add internal helper functions here.
********************************************************************************/

void add_to_ready(thread_t *thread) {
  if (manager->size_ready == 0) {
    manager->first_ready = thread;
  } else {
    manager->last_ready->next = thread;
  }

  manager->last_ready = thread;
  ++manager->size_ready;
}
/**
 * Adds a thread to the waiting queue.
 * @param thread the thread to add
 */ 
void add_to_waiting(thread_t *thread) {
  if (manager->size_waiting == 0) {
    manager->first_waiting = thread;
  } else {
    manager->last_waiting->next = thread;
  }

  manager->last_waiting = thread;
  ++manager->size_waiting;
}

/**
 * Adds a thread to the terminated queue.
 * @param thread the thread to add
 */
void add_to_terminated(thread_t *thread) {
  if (manager->size_terminated == 0) {
    manager->first_terminated = thread;
  } else {
    manager->last_terminated->next = thread;
  }

  manager->last_terminated = thread;
  manager->size_terminated++;
}


/**
 * Gets the first thread in the ready queue
 * return: NULL if the queue is empty otherwise the first thread in the ready queue
 */
thread_t *get_ready() {
  if (!manager->size_ready) return NULL;
  
  thread_t *thread = manager->first_ready;
  manager->first_ready = thread->next;
  thread->next = NULL;
  manager->size_ready--;
  return thread;
}

thread_t *get_waiting() {
  if (!manager->size_waiting) return NULL;
  
  thread_t *thread = manager->first_waiting;
  manager->first_waiting = thread->next;
  thread->next = NULL;
  manager->size_waiting--;
  return thread;
}

thread_t *get_terminated() {
  if (!manager->size_terminated) return NULL;
  
  thread_t *thread = manager->first_terminated;
  manager->first_terminated = thread->next;
  thread->next = NULL;
  manager->size_terminated--;
  return thread;
}




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
  if (manager == NULL) {
    manager = calloc(1, sizeof(thread_manager_t));
  } else {
    return -1;
  }
  if (manager == NULL) return -1;

  manager->first_ready = NULL;
  manager->last_ready = NULL;
  manager->first_waiting = NULL;
  manager->last_waiting = NULL;
  manager->first_terminated = NULL;
  manager->last_terminated = NULL;
  manager->running = NULL;
  manager->size_ready = 0;
  manager->size_waiting = 0;
  manager->size_terminated = 0;  
  manager->id_counter = 1;

  return 1;
}




/* Creates a new thread executing the start function.

   start - a function with zero arguments returning void.

   On success the positive thread ID of the new thread is returned. On failure a
   negative value is returned.
*/
tid_t spawn(void (*start)()){
  thread_t *thread = calloc(1, sizeof(thread_t));
  if (thread == NULL) return -1;
  puts("CALLOC in spawn SUCCESSFUL");

  
  thread->tid = manager->id_counter++;
  thread->state = ready;
  thread->next = NULL;
  thread->ctx.uc_link = NULL;
  thread->ctx.uc_stack.ss_sp = malloc(STACK_SIZE);
  thread->ctx.uc_stack.ss_size = STACK_SIZE;
  thread->ctx.uc_stack.ss_flags = 0;
  puts("manager updated");

  if (getcontext(&thread->ctx) == -1) {
    puts("getcontext failed");

    free(thread);
    return -1;
  }
  if (start == NULL) printf("Start == NULL");

  puts("getcontext SUCCESSFUL");

  makecontext(&thread->ctx, start, 0); // TODO: change 0 to something correct
  puts("makecontext SUCCESSFUL");     

  add_to_ready(thread);  
  //setcontext(&manager->first_ready->ctx);

  return thread->tid;
}



/* Cooperative scheduling

   If there are other threads in the ready state, a thread calling yield() will
   trigger the thread scheduler to dispatch one of the threads in the ready
   state and change the state of the calling thread from running to ready.
*/
void yield() {
  if (manager == NULL || manager->size_ready == 0 || manager->running == NULL) {
    return;
  }
  thread_t *old_thread = manager->running;
  add_to_ready(manager->running);
  manager->running =  get_ready();
  swapcontext(&old_thread->ctx, &manager->running->ctx);
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

void startup(){
  if (manager && manager->running == NULL) {
    thread_t *thread = get_ready();
    thread->state = running;
    manager->running = thread;
    setcontext(&thread->ctx);
  }
  
}