#ifndef CONDVAR_H
#define CONDVAR_H

#include <stdbool.h>
#include <pthread.h>
#include "mutex.h"

// Structure representing a conditional variable (condvar)
struct condvar {
  struct mutex mutex_op;        // Mutex for operations on the condvar
  struct condvar_node *front;   // Front of the thread queue
  struct condvar_node *rear;    // Rear of the thread queue
};

// Structure representing a node in the condvar thread queue
struct condvar_node {
  struct mutex mtx;             // Mutex associated with the node
  struct condvar_node *next;    // Pointer to the next node in the queue
};

// Initializes a conditional variable
void condvar_init(struct condvar *cv);

// Causes the current thread to wait on the conditional variable until signaled
void condvar_wait(struct condvar *cv, struct mutex *mtx);

// Signals one waiting thread to wake up from the conditional variable
void condvar_signal(struct condvar *cv);

// Signals all waiting threads to wake up from the conditional variable
void condvar_broadcast(struct condvar *cv);

#endif // CONDVAR_H
