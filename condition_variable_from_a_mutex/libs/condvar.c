#include "condvar.h"
#include <stdio.h>
#include <stdlib.h>

void condvar_init(struct condvar *cv)
{
  cv->rear = NULL;
  cv->front = NULL;
  mutex_init(&(cv->mutex_op));
}

void condvar_wait(struct condvar *cv, struct mutex *mtx)
{
  mutex_lock(&(cv->mutex_op)); // protegendo operações na fila

  struct condvar_node condvar_node; // crio novo no
  condvar_node.next = NULL; // inicializo nex 
  mutex_init(&(condvar_node.mtx)); // inicializo mutex
  
  if(cv->rear == NULL){ // fila vazia
    cv->front = &condvar_node; // adiciono no na fila
  } else { // fila não vazia
    cv->rear->next = &condvar_node; // adiciono no na fila
  }
  cv->rear = &condvar_node; // sempre será o ultimo

  // atomico????? no -> por mais que não seja, funciona como se fosse
  mutex_lock(&(condvar_node.mtx)); // garantindo que o novo mutex foi travado ao menos uma vez antes de 'dormir'
  
  mutex_unlock(mtx); // libero mutex principal para outras threads poderem acessa-lo
  mutex_unlock(&(cv->mutex_op)); // libero mutex de operações na fila

  mutex_lock(&(condvar_node.mtx)); // sleep de schrodinger
  mutex_lock(mtx); // tenta novamente adquirir o mutex principal
  mutex_unlock(&(condvar_node.mtx)); // apenas por garantia visto que dei lock mais acima
}

void condvar_signal(struct condvar *cv)
{
  mutex_lock(&(cv->mutex_op));
  struct condvar_node *condvar_front = cv->front;
  
  if(condvar_front == NULL) {
    mutex_unlock(&(cv->mutex_op));
    return;
  }

  cv->front = cv->front->next; // remove
  if(cv->front != NULL){
    cv->rear = NULL;
  }

  mutex_unlock(&(condvar_front->mtx));
  mutex_unlock(&(cv->mutex_op));
}

void condvar_broadcast(struct condvar *cv) // @todo - multiple threads
{
  mutex_lock(&(cv->mutex_op));
  struct condvar_node *condvar_front = cv->front;
  while(condvar_front != NULL){
    cv->front = cv->front->next; // remove

    mutex_unlock(&(condvar_front->mtx));

    condvar_front = cv->front;
  }
  cv->rear = NULL;
  mutex_unlock(&(cv->mutex_op));
}
