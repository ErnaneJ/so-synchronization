#include "libs/condvar.h"
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#define MAX_SIZE 10
int dados[MAX_SIZE];

struct condvar cv;
struct mutex main_mutex;
bool state = false;

volatile int inserir = 0;
volatile int remover = 0;

void *produtor(void *index)
{
  while(inserir < MAX_SIZE){
    mutex_lock(&main_mutex); // protege escrita dos dados
    dados[inserir] = rand(); // escreve 
    printf("T.%zu: Produzindo %d#%d\n", (size_t)index, inserir, dados[inserir]);
    state = true; // acabou de escrever, então libera
    mutex_unlock(&main_mutex); // libera o mutex principal

    condvar_signal(&cv);

    usleep(50000);
    inserir++;
  }

  return NULL;
}

void *consumidor(void *index)
{
  while(remover < MAX_SIZE) {
    mutex_lock(&main_mutex); // protege leitura dos dados
    
    while(!state){ // garanto que o produtor produziu
      printf("\n> T.%zu: Consumidor esperando\n\n", (size_t)index);
      condvar_wait(&cv, &main_mutex);
    }

    printf("T.%zu: Consumindo %d#%d\n", (size_t)index, remover, dados[remover]);
    state = remover < inserir;
    mutex_unlock(&main_mutex); // libera o mutex principal
    usleep(50000);
    remover++;
  }

  return NULL;
}

int main(void) {
  int err;
  pthread_t t1, t2;

  srand(time(NULL)); 

  condvar_init(&cv);
  mutex_init(&main_mutex);

  err = pthread_create(&t1, NULL, produtor, (void *)1);
  if (err) {
    fprintf(stderr, "Erro: %d\n", err);
    return 1;
  }

  err = pthread_create(&t2, NULL, consumidor, (void *)2);
  if (err) {
    fprintf(stderr, "Erro: %d\n", err);
    return 1;
  }

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  return 0;
}
