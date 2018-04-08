#ifndef __PORDER_H
#define __PORDER_H

#include"item.h"

enum STATUS{ RAISED=0, DELIVERED };
typedef struct Order
{
	int po_id;
	item_t item;
	int vendor_id;
	char v_company[60];
	enum STATUS status;
}porder_t;

void write_porder_in_file(porder_t *po);
void read_porder_from_file();
void display_porder();
int last_po_id(); // auto generated po_id
int find_purchase_order_by_name(char *purchase, porder_t *po_out);


#endif