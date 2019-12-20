#ifndef _CASHIER
#define _CASHIER
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "heapMin.h"

typedef struct cashier {
	QUEUE *customerList;
	HEAPMIN *customerPrioList;
	int heap, eta, nCustomers, nProducts, waitTime, number, speed;
} CASHIER;

int generateRandomSpeed();
int generateRandomProd();
int generateRandomCashier();
CASHIER* newCashier(int);
void available(CASHIER*,int);
void customerServed(CASHIER*);
void updateProducts(CASHIER*,int);
void updateWaitTime(CASHIER*,int);
void removeCustomer(CASHIER*);
QUEUE* getQueue(CASHIER*);
HEAPMIN* getMinHeap(CASHIER*);
int getCashier(CASHIER*);
int getETA(CASHIER*);
int getNCustomers(CASHIER*);
int getNProducts(CASHIER*);
int getWaitTime(CASHIER*);
int getSpeed(CASHIER*);
int getHeap(CASHIER*);
BOOL isEmpty(CASHIER*);

void handleCustomers(int,CASHIER*[],int);
void handleFirst(int,CASHIER*);
void postAC(CUSTOMER*,CASHIER*,int);
void addCustomer(CUSTOMER*,CASHIER*,int);
BOOL fullCashiers(CASHIER*[],int);
void printCashiers(CASHIER*[],int);
void printResults(CASHIER*[],int);
void runSim(int,int,int,int);

#endif