#ifndef __BILL_H
#define __BILL_H
#include"list.h"

typedef struct bill
{
	int day;
	int month;
	int year;
	int itemid;
	char customer_name[20];
	float total;
}bill_t;


void generate_bill(bill_t *b, list_t *cart_list);
void read_bill_from_file();
int last_bill_id();
void display_bill(bill_t *b);

#endif