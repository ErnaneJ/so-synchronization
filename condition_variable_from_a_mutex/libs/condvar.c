#include "condvar.h"
#include <stdio.h>
#include <stdlib.h>

// Initializes a condition variable
void condvar_init(struct condvar *cv) {
  cv->rear = NULL;
  cv->front = NULL;
  mutex_init(&(cv->mutex_op));  // Initializes the mutex for condvar operations
}

// Waits on the condition variable
void condvar_wait(struct condvar *cv, struct mutex *mtx) {
  mutex_lock(&(cv->mutex_op));  // Protects operations on the queue

  struct condvar_node condvar_node;  // Creates a new node
  condvar_node.next = NULL;  // Initializes the next pointer
  mutex_init(&(condvar_node.mtx));  // Initializes the mutex for the new node

  if (cv->rear == NULL) {  // Queue is empty
    cv->front = &condvar_node;  // Adds the node to the queue
  } else {  // Queue is not empty
    cv->rear->next = &condvar_node;  // Adds the node to the queue
  }
  cv->rear = &condvar_node;  // Updates the rear pointer

  mutex_lock(&(condvar_node.mtx));  // Ensures the new mutex is locked at least once before 'sleeping'

  mutex_unlock(mtx);  // Releases the main mutex to allow other threads to access it
  mutex_unlock(&(cv->mutex_op));  // Releases the mutex for queue operations

  mutex_lock(&(condvar_node.mtx));  // 'Schrodinger's sleep'
  mutex_lock(mtx);  // Attempts to acquire the main mutex again
  mutex_unlock(&(condvar_node.mtx));  // Just for safety, considering the lock above
}

// Signals (wakes up) one waiting thread on the condition variable
void condvar_signal(struct condvar *cv) {
  mutex_lock(&(cv->mutex_op));
  struct condvar_node *condvar_front = cv->front;

  if (condvar_front == NULL) {
    mutex_unlock(&(cv->mutex_op));
    return;
  }

  cv->front = cv->front->next;  // Removes the front node
  if (cv->front == NULL) {
    cv->rear = NULL;
  }

  mutex_unlock(&(condvar_front->mtx));  // Unlocks the mutex of the removed node
  mutex_unlock(&(cv->mutex_op));
}

// Signals (wakes up) all waiting threads on the condition variable
void condvar_broadcast(struct condvar *cv) {
  mutex_lock(&(cv->mutex_op));
  struct condvar_node *condvar_front = cv->front;

  while (condvar_front != NULL) {
    cv->front = cv->front->next;  // Removes the front node

    mutex_unlock(&(condvar_front->mtx));  // Unlocks the mutex of the removed node

    condvar_front = cv->front;
  }
  cv->rear = NULL;
  mutex_unlock(&(cv->mutex_op));
}
