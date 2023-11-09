#include "mutex.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

// Initializes a mutex
void mutex_init(struct mutex *m)
{
  m->mtx = malloc(sizeof(pthread_mutex_t)); // Allocates memory for pthread mutex
  pthread_mutex_init(m->mtx, NULL); // Initializes the pthread mutex
};

// Locks (acquires) the mutex
void mutex_lock(struct mutex *m)
{
  pthread_mutex_lock(m->mtx);
};

// Unlocks (releases) the mutex
void mutex_unlock(struct mutex *m)
{
  pthread_mutex_unlock(m->mtx);
};