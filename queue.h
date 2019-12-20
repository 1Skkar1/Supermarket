#ifndef _QUEUE
#define _QUEUE
#include <stdio.h>
#include <stdlib.h>
//#include "supermarket.h"


typedef enum {FALSE,TRUE} BOOL;

typedef struct fila{
	int inicio, fim, nmax, count;
	void** queue;
} QUEUE;

// criar fila com capacidade para n inteiros
QUEUE* mk_empty_queue(int n);
// colocar valor na fila
void enqueue(void*,QUEUE* f);
// retirar valor na fila
void* dequeue(QUEUE* f);
// verificar se a fila está vazia
BOOL queue_is_empty(QUEUE* f);
// verificar se a fila não admite mais elementos
BOOL queue_is_full(QUEUE* f);
// liberta fila
void free_queue(QUEUE* f);

int length(QUEUE* f);

#endif
