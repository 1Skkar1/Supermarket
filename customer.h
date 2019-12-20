#ifndef _CUSTOMER
#define _CUSTOMER
#include <stdio.h>
#include <stdlib.h>

typedef struct customer {
	int nItems, toa;
} CUSTOMER;

//CUSTOMER functions
CUSTOMER* newCustomer(int,int);
int getProducts(CUSTOMER*);
int getToA(CUSTOMER*);

#endif