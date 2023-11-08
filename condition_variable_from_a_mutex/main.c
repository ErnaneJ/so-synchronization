#include "libs/condvar.h"
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define TAMANHO 10
int dados[TAMANHO];

struct condvar cv;
struct mutex main_mutex;
bool state = false;

void *produtor(void *arg)
{
  int inserir = 0;
  while(inserir < TAMANHO){
    mutex_lock(&main_mutex); // protege escrita dos dados
    dados[inserir] = inserir; // escreve 
    printf("%zu: Produzindo %d\n", (size_t)arg, dados[inserir]);
    state = true; // acabou de escrever, então libera
    mutex_unlock(&main_mutex); // libera o mutex principal

    condvar_signal(&cv);

    usleep(50000);
    inserir++;
  }

  return NULL;
}

void *consumidor(void *arg)
{
  int remover = 0;
  while(remover < TAMANHO) {
    mutex_lock(&main_mutex); // protege leitura dos dados
    
    while(!state){ // garanto que o produtor produziu
      printf("%zu: Consumidor esperando\n", (size_t)arg);
      condvar_wait(&cv, &main_mutex);
    }

    printf("%zu: Consumindo %d\n", (size_t)arg, dados[remover]);
    state = false;
    mutex_unlock(&main_mutex); // libera o mutex principal
    usleep(50000);
    remover++;
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
