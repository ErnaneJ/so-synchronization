#ifndef MUTEX_H
#define MUTEX_H

#include <pthread.h>

// Structure representing a mutex
struct mutex {
  pthread_mutex_t *mtx;  // Pointer to the pthread mutex
};

// Initializes a mutex
void mutex_init(struct mutex *m);

// Locks (acquires) the mutex
void mutex_lock(struct mutex *m);

// Unlocks (releases) the mutex
void mutex_unlock(struct mutex *m);

#endif // MUTEX_H
