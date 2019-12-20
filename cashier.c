#include <stdio.h>
#include <stdlib.h>
#include "cashier.h"
#include "queue.h"
#include "heapMin.h"

#define MAX_CUSTOMERS 32

int generateRandomSpeed(){
	int random = 1 + rand() % 4;
	return random;
}

int generateRandomProd(int apet){
	int random = 1 + rand() % (3 * apet - 1);
	return random;
}

int generateRandomCashier(int nCashiers){
	int random = 1 + rand() % (nCashiers - 1);
	return random;
}

// 1 is queue
// 2 is heapmin
CASHIER* newCashier(int n){
	int randCashier = rand() % (2 + 1 - 1) + 1;
	CASHIER* s = malloc(sizeof(CASHIER));
	if(randCashier == 1){
		s -> customerList = mk_empty_queue(MAX_CUSTOMERS);
		s -> heap = 1;
		//printf("NORMAL CASHIER CREATED\n");
	}
	else if(randCashier == 2){
		s -> customerPrioList = build_heap_min(MAX_CUSTOMERS);
		s -> heap = 2;
		//printf("PRIO CASHIER CREATED\n");
	}
	s -> eta = 0;
	s -> nCustomers = 0;
	s -> nProducts = 0;
	s -> waitTime = 0;
	s -> number = n;
	s -> speed = generateRandomSpeed();
	return s;
}

void available(CASHIER* s, int val){
	s -> eta = val;
}

void customerServed(CASHIER* s){
	s -> nCustomers++;
}

void updateProducts(CASHIER* s, int val){
	s -> nProducts += val;
}

void updateWaitTime(CASHIER* s, int val){
	s -> waitTime += val;
}

void removeCustomer(CASHIER* s){
	if(s -> heap == 1)
		dequeue(s -> customerList);
	else
		extractMin(s -> customerPrioList);
}

//-----------------------------------------------

QUEUE* getQueue(CASHIER* s){
	return s -> customerList;
}

HEAPMIN* getMinHeap(CASHIER* s){
	return s -> customerPrioList;
}

int getCashier(CASHIER* s){
	return s -> number;
}

int getETA(CASHIER* s){
	return s -> eta;
}

int getNCustomers(CASHIER* s){
	return s -> nCustomers;
}

int getNProducts(CASHIER* s){
	return s -> nProducts;
}

int getWaitTime(CASHIER* s){
	return s -> waitTime;
}

int getSpeed(CASHIER* s){
	return s -> speed;
}

int getHeap(CASHIER* s){
	return s -> heap;
}

BOOL isEmpty(CASHIER* s){
	if(s -> heap == 1)
		return queue_is_empty(s -> customerList);
	else{
		if(heap_isEmpty(s -> customerPrioList) == 1)
			return TRUE;
		else
			return FALSE;
	}

}


//-----------------------------------------------

void handleCustomers(int step, CASHIER* cashierList[], int nCashiers){
	//size_t n = sizeof((CASHIER**)cashierList)/sizeof(int);
	for(int i=0; i<nCashiers; i++){
		//CASHIER* s = &cashierList[i];
		if(isEmpty(cashierList[i]))
			available(cashierList[i],step);
		else
			handleFirst(step,cashierList[i]);
	}
}

void handleFirst(int step, CASHIER* s){
	CUSTOMER *customer = (CUSTOMER *)malloc(sizeof(CUSTOMER));
	//QUEUE* q = (QUEUE *)malloc(sizeof(QUEUE));
	//HEAPMIN* qmin = (HEAPMIN *)malloc(sizeof(HEAPMIN));

	if(s -> heap == 1){
		QUEUE* q = (QUEUE *)malloc(sizeof(QUEUE));
		q = getQueue(s);
		customer = q -> queue[q->inicio];
	}
	else{
		HEAPMIN* q = (HEAPMIN *)malloc(sizeof(HEAPMIN));
		q = getMinHeap(s);
		customer = firstHeap(q);
	}

	int wait = step - getETA(s);
	int processed = wait * getSpeed(s);
	//printf("HELLO THERE PROCESSED %d\n", processed);
	if(processed >= customer -> nItems){
		available(s,step+1);
		customerServed(s);
		updateProducts(s,customer -> nItems);
		updateWaitTime(s,step-customer -> toa);
		removeCustomer(s);
		printf("<-- Cliente atendido na caixa %d\n", s -> number);
		printf("\n");
	}
}

void postAC(CUSTOMER* newC, CASHIER* chosenCashier, int heapID){
	if(heapID == 1)
		enqueue((CUSTOMER*)newC,getQueue(chosenCashier));
	else
		insert((CUSTOMER*)newC,getMinHeap(chosenCashier));
}

void addCustomer(CUSTOMER* newC, CASHIER* cashierList[], int nCashiers){
	int items = newC -> nItems;
	//printf("blablablabla %d\n",items);
	int chosenCashier = -1, betterCashier = 100;
	if(items <= 10){
		for(int i=0; i<nCashiers; i++){
			if(getHeap(cashierList[i]) == 2){
				//printf("PRIO ---- %d\n", cashierList[i]->customerPrioList->size);
				if(cashierList[i]->customerPrioList->size == 0){
					//printf("HEREONI \n");
					chosenCashier = i;
					//printf("pre %d\n", chosenCashier);
					postAC(newC,cashierList[chosenCashier],2);
					return;
				}
			}
		}

		if(chosenCashier = -1){
			for(int j=0; j<nCashiers; j++){
				if(getHeap(cashierList[j]) == 1){
					if(length(cashierList[j]->customerList) == 0){
						chosenCashier = j;
						postAC(newC,cashierList[chosenCashier],1);
						return;
					}
				}
			}
		}

		if(chosenCashier = -1){
			for(int k=0; k<nCashiers; k++){
				if(getHeap(cashierList[k]) == 2){
					if(cashierList[k]->customerPrioList->size < betterCashier){
						betterCashier = cashierList[k]->customerPrioList->size;
						chosenCashier = k;
					}
				}
			}
			if(chosenCashier != -1){
				postAC(newC,cashierList[chosenCashier],2);
				return;
			}
		}

		if(chosenCashier = -1){
			for(int l=0; l<nCashiers; l++){
				if(getHeap(cashierList[l]) == 1){
					if(length(cashierList[l]->customerList) < betterCashier){
						betterCashier = length(cashierList[l]->customerList);
						chosenCashier = l;
					}
				}
			}
			if(chosenCashier != -1){
				postAC(newC,cashierList[chosenCashier],1);
				return;
			}
		}
	}
	else{
		for(int i=0; i<nCashiers; i++){
			if(getHeap(cashierList[i]) == 1){
				if(length(cashierList[i]->customerList) == 0){
					chosenCashier = i;
					postAC(newC,cashierList[chosenCashier],1);
					return;
				}
			}
		}

		if(chosenCashier = -1){
			for(int j=0; j<nCashiers; j++){
				if(getHeap(cashierList[j]) == 2){
					if(cashierList[j]->customerPrioList->size == 0){
						chosenCashier = j;
						postAC(newC,cashierList[chosenCashier],2);
						return;
					}
				}
			}
		}

		if(chosenCashier = -1){
			for(int k=0; k<nCashiers; k++){
				if(getHeap(cashierList[k]) == 1){
					if(length(cashierList[k]->customerList) < betterCashier){
						betterCashier = length(cashierList[k]->customerList);
						chosenCashier = k;
					}
				}
			}
			if(chosenCashier != -1){
				postAC(newC,cashierList[chosenCashier],1);
				return;
			}
		}

		if(chosenCashier = -1){
			for(int l=0; l<nCashiers; l++){
				if(getHeap(cashierList[l]) == 2){
					if(cashierList[l]->customerPrioList->size < betterCashier){
						betterCashier = cashierList[l]->customerPrioList->size;
						chosenCashier = l;
					}
				}
			}
			if(chosenCashier != -1){
				postAC(newC,cashierList[chosenCashier],2);
				return;
			}
		}
	}
	/*
	printf("%d\n", chosenCashier);
	if(cashierList[chosenCashier] -> heap == 1)
		enqueue((CUSTOMER*)newC,getQueue(cashierList[chosenCashier]));
	else
		insert((CUSTOMER*)newC,getMinHeap(cashierList[chosenCashier]));
	*/
}

BOOL fullCashiers(CASHIER* cashierList[], int nCashiers){
	//size_t n = sizeof((CASHIER**)cashierList)/sizeof(int);
	for(int i=0; i<nCashiers; i++){
		//CASHIER* s = &cashierList[i];
		if(!isEmpty(cashierList[i]))
			return TRUE;
	}
	return FALSE;
}

void printCashiers(CASHIER* cashierList[], int nCashiers){
	//size_t n = sizeof((CASHIER**)cashierList)/sizeof(int);
	for(int i=0; i<nCashiers; i++){
		//CASHIER* s = &cashierList[i];
		printf("> CAIXA %d:\n", cashierList[i] -> number);
		/*for (int j = 0; (CUSTOMER *)(cashierList[i]->customerList->queue[j]) != NULL; i++) {
			printf("Items do chefe %d\n", getProducts(cashierList[i]->customerList->queue[j]));
		}*/
		printf("Produtos por ciclo: %d\n ", cashierList[i] -> speed);
		printf("Clientes atendidos: %d\n ", cashierList[i] -> nCustomers);
		printf("Produtos processados: %d\n ", cashierList[i] -> nProducts);
		printf("Tempo de espera: %d\n ", cashierList[i] -> waitTime);
		printf("ETA: %d\n ", cashierList[i] -> eta);
		printf("------------------------------------------\n");

	}
}

void printResults(CASHIER* cashierList[], int nCashiers){
	//size_t n = sizeof((CASHIER**)cashierList)/sizeof(int);
	for(int i=0; i<nCashiers; i++){
		//CASHIER* s = &cashierList[i];
		printf("> CAIXA %d:\n ", cashierList[i] -> number);
		printf("Produtos por ciclo: %d\n ", cashierList[i] -> speed);
		printf("Clientes atendidos: %d\n ", cashierList[i] -> nCustomers);

		if(getNCustomers(cashierList[i]) != 0)
			printf("Média de %.1d produtos por cliente\n ", cashierList[i] -> nProducts / cashierList[i] -> nCustomers);
		printf("------------------------------------------\n");
	}
}

void runSim(int affluence, int apet, int nCashiers, int nCycles){
	int nProducts, i, k;
	int randCustomer;
	CASHIER* cashierList[nCashiers];
	for(i=0; i<nCashiers; i++){
		cashierList[i] = newCashier(i+1);
		//printf("%d",cashierList[i] -> number);
	}
		//printf("%d",cashierList[0] -> number);
	for(k=1; k<nCycles+1; k++){
		printf("\t/-- CICLO %d --\\ \n", k);

		randCustomer = rand() % 10;

		if(randCustomer <= affluence / 10){
			nProducts = generateRandomProd(apet);
			CUSTOMER* newC = newCustomer(nProducts,k);
			printf("\n");
			printf("--> Cliente criado com %d produtos\n", nProducts);
			int chosenCashier = generateRandomCashier(nCashiers);
			//printf("CHOSEN: %d\n", chosenCashier);
			//printf("HERE1\n");
			addCustomer(newC,cashierList,nCashiers);
			//printf("HERE1.5\n");
			//printf("%d\n", length(cashierList[chosenCashier-1]->customerList));
		}
		//printf("HERE2\n");
		printf("\n");
		printCashiers(cashierList,nCashiers);
		handleCustomers(k,cashierList,nCashiers);
		
	}
	printf("\n");
	printf("+---------------------+\n");
	printf("|-- FECHO DE CAIXAS --|\n");
	printf("+---------------------+\n\n");
	k = nCycles + 1;

	while(fullCashiers(cashierList,nCashiers)){
		printf("\t/-- CICLO %d --\\ \n\n", k);
		printCashiers(cashierList,nCashiers);
		handleCustomers(k,cashierList,nCashiers);
		k = k + 1;
	}
	printf("\n");
	printf("+------------------+\n");
	printf("|-- ESTATÍSTICAS --|\n");
	printf("+------------------+\n\n");
	printResults(cashierList,nCashiers);
}