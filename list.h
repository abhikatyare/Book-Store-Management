#ifndef __LIST_H
#define __LIST_H
#include"item.h"

typedef struct node
{
	item_t item;
	struct node *next;
}node_t;

typedef struct list
{
	int count;
	node_t *head;
}list_t;

void init_head(list_t *list);
void input_in_list(item_t *itm);
node_t * create(item_t *itm);
void display(item_t *itm);
void addlast(item_t itm, list_t *l);
void display_list(list_t *l);
void write_form_link_list_to_stock(list_t *l);
void load_item_from_stock_to_link_list(list_t *l);
void find_item_in_list(char *pname, list_t *l,list_t *cart_list);
float total(list_t *cart_list);

#endif

