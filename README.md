# Supermarket
Programming Lab - Second Project - Supermarket

May 27th 2019

### Compile:
  ```bash
  gcc -o super main.c customer.c cashier.c queue.c heapMin.c
  ```
 
### Run:
  ```bash
  ./super
  ```
  
After compiling and executing the implementation, it will ask for input for 4 variables:

> ***Afluência:*** Affluence -> percentage of the supermarket's popularity. The higher it is the more customers it will have.

> ***Apetência:*** Appetence -> probability percentage of customers will to buy products. The higher it is the more items they'll purchase.

> ***Número de caixas:*** Number of cashiers -> Number of open cashiers in the supermarket.

> ***Número de ciclos:*** Number of cycles -> Number of customers the cashiers will process before closing the supermarket. Each cycle allows a customer in each cashier. After all the cycles are done no more customers may enter but the cashiers will keep processing the remaining customers inside for as many cycles necessary.
