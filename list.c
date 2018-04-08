#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"item.h"
#include"bill.h"



void init_head(list_t *list)
{
	list->head = NULL;
	list->count = 0;
}



node_t * create(item_t *itm)
{
	node_t * new = (node_t*)malloc(sizeof(node_t));
	new->item = *itm;
	new->next = NULL;
	return new;
}

void display(item_t *itm)
{
	itm->total = itm->quantity*itm->unit_price;
	printf("\n\t\t%d\t%s\t%s\t\t%d\t\t%.2f\t\t%.2f", itm->itemid ,itm->product_Name,itm->product_Description,itm->quantity,itm->unit_price,itm->total);
}


void addlast(item_t itm, list_t *l)
{
	node_t * new = create(&itm);
	if (l->head == NULL)
	{
		l->head = new;
	}
	else
	{
		node_t *temp = l->head;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = new;
	}
}

void display_list(list_t *l)
{
	node_t *temp = l->head;
	printf("\n\t\t-----------------------------------------------------------------------");
	printf("\n\t\tItem_Id\tName\tDescription\tQuantity\tUnit Price\tTotal");
	printf("\n\t\t-----------------------------------------------------------------------");
	while (temp != NULL)
	{
		display(&temp->item);
		temp = temp->next;
	}
	printf("\n\t\t-----------------------------------------------------------------------");
}


void write_form_link_list_to_stock(list_t *l)
{
	FILE *fp;
	fp = fopen("stock.dat", "wb");
	if (fp == NULL)
	{
		printf("\nUnable to Open");
		return;
	}
	else
	{
		node_t *temp = l->head;
		while (temp != NULL)
		{
			fwrite(&temp->item, sizeof(item_t), 1, fp);
			temp = temp->next;
		}
	}
	fclose(fp);
}


void load_item_from_stock_to_link_list(list_t *l)
{
	FILE *fp;
	item_t itm;
	fp = fopen("stock.dat", "rb");
	if (fp == NULL)
	{
		return;
	}
	else
	{
		while (fread(&itm, sizeof(item_t), 1, fp) != 0)
		{
			addlast(itm,l);
		}
		display_list(l);
	}
	fclose(fp);
}



void find_item_in_list(char *pname,list_t *l,list_t *cart_list)
{
	node_t *temp=l->head;
	int quantity,real_quantity;
	while (temp != NULL)
	{
		if (strcmp(pname, temp->item.product_Name) == 0)
		{
			printf("\n\t\t-----------------------------------------------------------------------");
			display(&temp->item);
			printf("\n\t\t-----------------------------------------------------------------------");
			printf("\nEnter the Quantity::");
			scanf("%d",&quantity);
			real_quantity = temp->item.quantity;
			temp->item.quantity = quantity;
			printf("\n Quantity in Cart::%d", temp->item.quantity);
			addlast(temp->item, cart_list);
			temp->item.quantity = real_quantity;
			temp->item.quantity = temp->item.quantity - quantity;
			printf("\n Quantity in Stock::%d", temp->item.quantity);
			return;
		}
		temp = temp->next;
	}
}




float total(list_t *cart_list)
{
	float i=0;
	node_t *temp = cart_list->head;
	while (temp != NULL)
	{
		i+=temp->item.total;
		temp = temp->next;
	}
	return i;
}