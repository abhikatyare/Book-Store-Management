#ifndef __CUSTOMER_H
#define __CUSTOMER_H

typedef struct customer
{
	char name[30];
	char lastname[30];
	char email[30];
	char contact[30];
}customer_t;

void write_customer_in_file(customer_t *cust);
void read_customer_from_file();
int find_customer(char *number, customer_t *cu);

#endif