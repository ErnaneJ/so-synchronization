#include "libs/condvar.h"
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define TAMANHO 10

int inserir = 0;
int remover = 0;

int dados[TAMANHO];

struct condvar cv;
struct mutex main_mutex;

void *produtor(void *arg)
{
  for (; inserir < TAMANHO; inserir++) {
    condvar_signal(&cv);
    condvar_wait(&cv, &main_mutex);
    
    printf("%zu: Produzindo %d\n", (size_t)arg, inserir);
    dados[inserir] = inserir;
    usleep(50000);

    condvar_broadcast(&cv);
  }

  return NULL;
}

void *consumidor(void *arg)
{
  for (; remover < TAMANHO; remover++) {
    condvar_signal(&cv);
    condvar_wait(&cv, &main_mutex);

    printf("%zu: Consumindo %d\n", (size_t)arg, dados[remover]);
    usleep(50000);

    condvar_broadcast(&cv);
  }

  return NULL;
}

int main(void) {
  int err;
  pthread_t t1, t2;

  condvar_init(&cv);
  mutex_init(&main_mutex);

  err = pthread_create(&t1, NULL, produtor, (void *)0);
  if (err) {
    fprintf(stderr, "Erro: %d\n", err);
    return 1;
  }

  err = pthread_create(&t2, NULL, consumidor, (void *)1);
  if (err) {
    fprintf(stderr, "Erro: %d\n", err);
    return 1;
  }

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  return 0;
}
