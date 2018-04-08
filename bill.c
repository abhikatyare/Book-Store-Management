#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"list.h"
#include"customer.h"
#include"bill.h"




int last_bill_id()
{
	FILE *fp;
	int id = 0;
	bill_t b;
	int size;
	size = sizeof(b);
	fp = fopen("bill.dat", "rb");
	if (fp == NULL)
	{
		return 0;
	}
	else
	{
		if (fseek(fp, -size, SEEK_END) == -1)
			return 0;
		fseek(fp, -size, SEEK_END);
		fread(&b, sizeof(b), 1, fp);
		id = b.itemid;
	}
	fclose(fp);
	return id;
}




void generate_bill(bill_t *b,list_t *cart_list)
{
	FILE *fp;
	int ret;
	char no[20];
	customer_t c;
	printf("\n\n\t\tEnter the No of Customer::");
	scanf("%s",no);
	printf("\t\tEnter Day		::");
	scanf("%d", &b->day);
	printf("\t\tEnter Month		::");
	scanf("%d", &b->month);
	printf("\t\tEnter Year		::");
	scanf("%d", &b->year);
	system("cls");
	b->itemid = last_bill_id() + 1;
	printf("\n\t\t=======================================================================\n");
	printf("\t\t\t\t\t\tBILL NO::%d", b->itemid);
	ret=find_customer(no, &c);
	if (ret == 1)
	{
		strcpy(b->customer_name, c.name);
		printf("\n\n\t\tName::%s", c.name);
	}
	else
	{
		printf("\n\n\t\tCustomer not Present PLEASE REGISTER");
	}
	printf("\t\t\t\t\t\tDate::%d/%d/%d",b->day,b->month,b->year);
	display_list(cart_list);
	b->total = total(cart_list);
	printf("\n\t\t\t\t\t\t\t\t\tTotal::%.2f",b->total);
	printf("\n\t\t=======================================================================");
	fp = fopen("bill.dat", "ab");
	if (fp == NULL)
	{
		return;
	}
	else
	{
		fwrite(b, sizeof(bill_t), 1, fp);
	}
	fclose(fp);
	
}

void display_bill(bill_t *b)
{
	printf("\n\t\t%d\t\t%s\t%d/%d/%d\t%.2f", b->itemid, b->customer_name, b->day, b->month, b->year, b->total);
}

void read_bill_from_file()
{
	FILE *fp;
	bill_t b;
	fp = fopen("bill.dat", "rb");
	if (fp == NULL)
	{
		return;
	}
	else
	{
		printf("\n\t\t=======================================================================");
		printf("\n\t\tBill No\t\tName\t\tDate\t\tTotal");
		printf("\n\t\t-----------------------------------------------------------------------");
		while (fread(&b, sizeof(b), 1, fp) != 0)
		{
			display_bill(&b);
		}
		printf("\n\t\t=======================================================================");
	}
	fclose(fp);
}



