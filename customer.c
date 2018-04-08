#include<stdio.h>
#include<string.h>
#include"customer.h"



void write_customer_in_file(customer_t *cst)		
{
	FILE *fp;
	customer_t c;
	printf("\n\n\t\tEnter the Name of Customer		::");
	scanf("%s", c.name);
	printf("\t\tEnter the Last Name of Customer		::");
	scanf("%s", c.lastname);
	printf("\t\tEnter the Email of Customer		::");
	scanf("%s", c.email);
	printf("\t\tEnter the Contact of Customer		::");
	scanf("%s", c.contact);
	fp = fopen("customer.dat", "ab+");
	if (fp == NULL)
	{
		return;
	}
	else
	{
		fwrite(&c, sizeof(c), 1, fp);
	}
	fclose(fp);
}



void read_customer_from_file()
{
	FILE *fp;
	customer_t c;
	fp = fopen("customer.dat", "rb");
	if (fp == NULL)
	{
		return;
	}
	else
	{
		printf("\n\t\t-----------------------------------------------------------------------");
		printf("\n\t\tName\t\tLastname\tEmail\t\tContact");
		printf("\n\t\t-----------------------------------------------------------------------");
		while ((fread(&c, sizeof(c), 1, fp)) != 0)
		{
			printf("\n\t\t%s\t%s\t\t%s\t%s", c.name, c.lastname, c.email, c.contact);
		}
		printf("\n\t\t-----------------------------------------------------------------------");
	}
	fclose(fp);
}

int find_customer(char *number, customer_t *cu)//find customer using name & collect in out parameter
{
	FILE *fp;
	customer_t c;
	int flag=0;
	fp = fopen("customer.dat", "rb");
	if (fp == NULL)
	{
		return flag;
	}
	while (fread(&c, sizeof(c), 1, fp) != 0)
	{
		if (strcmp(number,c.contact)==0)
		{
			*cu = c;
			flag = 1;
		}
	}
	fclose(fp);
	return flag;
}































































