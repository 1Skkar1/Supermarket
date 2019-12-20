#ifndef MINHEAP_H
#define MINHEAP_H
#include<stdio.h>
#include<stdlib.h>
#include "customer.h"
//#include "supermarket.h"

typedef struct heapMin {
  int sizeMax, size;
  CUSTOMER **customers;
  int *pos_a;
} HEAPMIN;

//---------  protótipos das funções disponíveis --------------------

HEAPMIN *build_heap_min(int n);
void insert(CUSTOMER* v, HEAPMIN *q);
CUSTOMER* extractMin(HEAPMIN *q);   // retorna v 
void decreaseKey(CUSTOMER* v, int newkey, HEAPMIN *q);
int heap_isEmpty(HEAPMIN *q);   // retorna 1 ou 0
CUSTOMER* firstHeap(HEAPMIN *q);

void write_heap(HEAPMIN *q);
void destroy_heap(HEAPMIN *q);


//----------------- definição das funções e macros ---------------------

#define POSINVALIDA 0

#define LEFT(i) (2*(i))
#define RIGHT(i) (2*(i)+1)
#define PARENT(i) ((i)/2)

static void heapify(int i,HEAPMIN *q);
static void swap(int i,int j,HEAPMIN *q);
static int compare(int i, int j, HEAPMIN *q);
static int pos_valida(int i,HEAPMIN *q);

#endif

    