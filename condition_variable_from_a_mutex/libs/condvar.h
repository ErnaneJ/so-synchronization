#ifndef CONDVAR_H
#define CONDVAR_H

#include <stdbool.h>
#include <pthread.h>
#include "mutex.h"

struct condvar {
  bool flag;
  struct mutex *mtx;
};

void condvar_init(struct condvar *cv);
void condvar_wait(struct condvar *cv, struct mutex *mtx);
void condvar_signal(struct condvar *cv);
void condvar_broadcast(struct condvar *cv);

#endif // CONDVAR_H