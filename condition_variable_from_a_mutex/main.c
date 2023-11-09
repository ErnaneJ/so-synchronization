#include "libs/condvar.h"
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#define MAX_SIZE 10
int data[MAX_SIZE];

struct condvar cv;
struct mutex main_mutex;
bool isProducing = false;

int insertIndex = 0;

void *producer(void *index) {
  while (insertIndex < MAX_SIZE) {
    mutex_lock(&main_mutex);  // Protects data writing
    data[insertIndex] = rand();  // Writes to data
    printf("T.%zu: Producing %d#%d\n", (size_t)index, insertIndex, data[insertIndex]);
    isProducing = true;  // Indicates that data is ready
    mutex_unlock(&main_mutex);  // Releases the main mutex

    condvar_broadcast(&cv);  // Wakes up waiting threads

    usleep(50000);

    insertIndex++;
  }

  return NULL;
}

void *consumer(void *index) {
  int removeIndex = 0;
  while (removeIndex < MAX_SIZE) {
    mutex_lock(&main_mutex);  // Protects data reading
    
    while (!isProducing) {  // Ensures that the producer has produced
      printf("\n> T.%zu: Consumer waiting\n\n", (size_t)index);
      condvar_wait(&cv, &main_mutex);
    }

    printf("T.%zu: Consuming %d#%d\n", (size_t)index, removeIndex, data[removeIndex]);
    isProducing = removeIndex < insertIndex;  // Continues consuming if there is still data
    mutex_unlock(&main_mutex);  // Releases the main mutex
    usleep(50000);
    removeIndex++;
  }

  return NULL;
}

int main(void) {
  int err;
  pthread_t producerThread, consumerThread;

  srand(time(NULL)); 

  condvar_init(&cv);
  mutex_init(&main_mutex);

  err = pthread_create(&producerThread, NULL, producer, (void *)1);
  if (err) {
    fprintf(stderr, "Error: %d\n", err);
    return 1;
  }

  err = pthread_create(&consumerThread, NULL, consumer, (void *)2);
  if (err) {
    fprintf(stderr, "Error: %d\n", err);
    return 1;
  }

  pthread_join(producerThread, NULL);
  pthread_join(consumerThread, NULL);

  return 0;
}
