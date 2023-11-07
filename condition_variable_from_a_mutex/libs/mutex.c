#include "mutex.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

void mutex_init(struct mutex *m)
{
  m->mtx = malloc(sizeof(pthread_mutex_t));
  pthread_mutex_init(m->mtx, NULL);
};

void mutex_lock(struct mutex *m)
{
  pthread_mutex_lock(m->mtx);
};

void mutex_unlock(struct mutex *m)
{
  pthread_mutex_unlock(m->mtx);
};