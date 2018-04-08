#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"porder.h"
#include"list.h"



void input_items(item_t *item, list_t *l)
{
	FILE *fp;
	porder_t p, pt;
	int flag, size;
	char pname[20],ch;
	size = sizeof(pt);
	item->itemid = last_item_id() + 1;
 p:	printf("\n\t\tEnter Product Name::");
	scanf("%s", pname);
	strcpy(item->product_Name, pname); //copy product name in anticipation
	flag = find_purchase_order_by_name(pname, &p);
	if (flag == 1)
	{
		if (find_item_by_name(pname, item, l) != 1)
		{

			strcpy(item->product_Name, p.item.product_Name);
			strcpy(item->product_Description, p.item.product_Description);
			item->quantity = p.item.quantity;
			item->unit_price = p.item.unit_price;
			printf("\n\t\t------------------------");
			printf("\n\t\tPo_Id		::%d", p.po_id);
			printf("\n\t\tDescription	::%s", item->product_Description);
			printf("\n\t\tUnit Price	::%.2f", item->unit_price);
			printf("\n\t\t------------------------");
			printf("\n\t\tQuantity	::%d", item->quantity);
			printf("\n\t\t------------------------");
		}
		

		fp = fopen("order.dat", "rb+");
		if (fp == NULL)
		{
			return;
		}
		while (fread(&pt, sizeof(pt), 1, fp) != 0)
		{
			if (strcmp(item->product_Name, pt.item.product_Name) == 0)
			{

				pt.status = DELIVERED;
				fseek(fp, -size, SEEK_CUR);
				fwrite(&pt, sizeof(pt), 1, fp);
				fclose(fp);
			}

		}

	}
	else
	{
		printf("\n\t\tItem Not Found");
		printf("\nCreate Purchase Order ? (Y/N) ::");
		goto p;
	}
}


void write_updated_po_in_file(porder_t *po)
{
	porder_t pt;
	int size;
	FILE *fp;
	size = sizeof(pt);
	fp = fopen("order.dat", "rb+");
	if(fp == NULL)
	{
		return;
	}
	while(fread(&pt, sizeof(pt), 1, fp) != 0)
	{
		if(strcmp(po->item.product_Name, pt.item.product_Name) == 0 && pt.status==RAISED)
		{

			pt.status = DELIVERED;
			fseek(fp, -size, SEEK_CUR);
			fwrite(po, sizeof(pt), 1, fp);
			fclose(fp);
		}

	}
}


void write_item_in_file(item_t *item, list_t *l)
{
	int check;
	item_t it;
	porder_t po;

	node_t *trav = l->head;

	input_items(item, l);

	check = find_item_by_name(item->product_Name, &it, l);
	if (check == 1)
	{
		find_purchase_order_by_name(item->product_Name, &po);
		while (trav != NULL)
		{
			if (strcmp(trav->item.product_Name, item->product_Name) == 0)
			{
				trav->item.quantity = it.quantity + po.item.quantity;//adding old q with new q
				po.status =DELIVERED ;
				write_updated_po_in_file(&po); //update status at appropri
				break;
			}
			trav = trav->next;
		}

	}
	else
	{
		//input_items(item);
		addlast(*item, l);
	}
}



void display_item(item_t *it)
{
	printf("\n\t\t%d\t%s\t%s\t\t%d\t\t%.2f", it->itemid, it->product_Name, it->product_Description, it->quantity, it->unit_price);
}



void read_item_from_file()
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
		printf("\n\t\t--------------------------------------------------------------");
		printf("\n\t\tItem_Id\tName\tDescription\tQuantity\tUnit Price");
		printf("\n\t\t--------------------------------------------------------------");

		while (fread(&itm, sizeof(item_t), 1, fp) != 0)//read file till EOF
		{
			display_item(&itm);//Display the file contents one after another
		}
		printf("\n\t\t--------------------------------------------------------------");
	}
}



int find_item_by_name(char *pname, item_t *itout, list_t *l)
{

	int flag = 0;
	node_t *trav;
	trav = l->head;


	while (trav != NULL)
	{
		if (strcmp(trav->item.product_Name, pname) == 0)
		{
			*itout = trav->item;
			flag = 1;
			break;
		}

		trav = trav->next;
	}
	return flag;
}



int last_item_id()
{
	FILE *fp;
	int id = 0;
	item_t a;
	int size;
	size = sizeof(a);
	fp = fopen("stock.dat", "rb");
	if (fp == NULL)
	{
		return 0;
	}
	else
	{
		if (fseek(fp, -size, SEEK_END) == -1)
			return 0;
		fseek(fp, -size, SEEK_END);
		fread(&a, sizeof(a), 1, fp);
		id = a.itemid;
	}
	fclose(fp);
	return id;
}
