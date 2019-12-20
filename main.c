#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "queue.h"
//#include "supermarket.h"
#include "customer.h"
#include "cashier.h"

int main(){
	int affluence, apet, nCashiers, nCycles;
	printf("\t+----------------------------+\n");
	printf("\t|-- WELCOME TO SUPERMARKET --|\n");
	printf("\t+----------------------------+\n");
	printf("Give values to the following variables\n");
	printf("Afluência: ");
	scanf("%d",&affluence);
	printf("Apetência: ");
	scanf("%d",&apet);
	printf("Número de caixas: ");
	scanf("%d",&nCashiers);
	printf("Número de ciclos: ");
	scanf("%d",&nCycles);
	runSim(affluence,apet,nCashiers,nCycles);
	return 0;
}