#include "condvar.h"
#include <stdio.h>
#include <stdlib.h>

void condvar_init(struct condvar *cv)
{
  struct mutex mtx;
  cv->mtx = &mtx;
  cv->flag = false;
  mutex_init(cv->mtx);
}

void condvar_wait(struct condvar *cv, struct mutex *mtx)
{
    mutex_unlock(mtx);
    
    mutex_lock(cv->mtx);
    cv->flag = true;
    mutex_unlock(cv->mtx);

    // Aguarda até ser sinalizado
    while (cv->flag) {
      mutex_unlock(mtx);
      mutex_lock(cv->mtx);
      mutex_lock(mtx);
    }
}

void condvar_signal(struct condvar *cv)
{
  mutex_lock(cv->mtx);
  if (cv->flag) {
    cv->flag = false;
    mutex_unlock(cv->mtx);
  }
}

void condvar_broadcast(struct condvar *cv) // @todo - multiple threads
{
  mutex_lock(cv->mtx);
  if (cv->flag) {
    cv->flag = false;
    mutex_unlock(cv->mtx);
  }
}
