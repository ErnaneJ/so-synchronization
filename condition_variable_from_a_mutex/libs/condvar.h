#ifndef CONDVAR_H
#define CONDVAR_H

#include <stdbool.h>
#include <pthread.h>
#include "mutex.h"

struct condvar {
  struct mutex mutex_op;
  struct condvar_node *front;
  struct condvar_node *rear;
};

struct condvar_node {
  struct mutex mtx;
  struct condvar_node *next;
};

void condvar_init(struct condvar *cv);
void condvar_wait(struct condvar *cv, struct mutex *mtx);
void condvar_signal(struct condvar *cv);
void condvar_broadcast(struct condvar *cv);

#endif // CONDVAR_H