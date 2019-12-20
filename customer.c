#include <stdio.h>
#include <stdlib.h>
#include "customer.h"

CUSTOMER* newCustomer(int items, int arrival){
	CUSTOMER *c = malloc(sizeof(CUSTOMER));
	c -> nItems = items;
	c -> toa = arrival;
	return c;
}

int getProducts(CUSTOMER *c){
	return c -> nItems;
}

int getToA(CUSTOMER *c){
	return c -> toa;
}