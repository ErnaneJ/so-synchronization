#ifndef MUTEX_H
#define MUTEX_H

#include <pthread.h>

struct mutex {
  pthread_mutex_t *mtx;
};

void mutex_init(struct mutex *m);
void mutex_lock(struct mutex *m);
void mutex_unlock(struct mutex *m);

#endif // MUTEX_H
