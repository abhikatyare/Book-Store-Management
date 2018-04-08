#ifndef __ITEM_H
#define __ITEM_H

typedef struct list list_t;  //forward declaration

typedef struct Item
{
	int itemid;
	char product_Name[100];
	char product_Description[100];
	int  quantity;
	float unit_price;
	float total;
}item_t;

void input_items(item_t *item,list_t *l);
void read_item_from_file();
int find_item_by_name(char *pname, item_t *update,list_t *l);
void display_item(item_t *it);
int last_item_id();
int find_item_in_stock(char *pname, item_t *update);
void write_item_in_file(item_t *item, list_t *l);

#endif