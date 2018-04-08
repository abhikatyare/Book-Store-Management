#include<stdio.h>
#include"vendor.h"

void write_vendor_in_file(vendor_t *cust)
{
	FILE *fp;
	vendor_t v;
	v.vendor_id = last_vendor_id() + 1;
	printf("\n\t\tEnter the Company of Vendor	::");
	scanf("%s", v.company);
	printf("\t\tEnter the Name of Vendor	::");
	scanf("%s", v.name);
	printf("\t\tEnter the Last Name of Vendor	::");
	scanf("%s", v.lastname);
	printf("\t\tEnter the Email of Vendor	::");
	scanf("%s", v.email);
	printf("\t\tEnter the Contact of Vendor	::");
	scanf("%s", v.contactNo);
	printf("\t\tEnter the Account No of Vendor	::");
	scanf("%s", v.accountNo);
	printf("\t\tEnter the Discount		::");
	scanf("%f", &v.discount);
	fp = fopen("vendor.dat", "ab+");
	if (fp == NULL)
	{
		return;
	}
	else
	{
		fwrite(&v, sizeof(v), 1, fp);
	}
	fclose(fp);
}


void read_vendor_from_file()
{
	FILE *fp;
	vendor_t v;
	fp = fopen("vendor.dat", "rb");
	if (fp == NULL)
	{
		return;
	}
	else
	{
		printf("\n\t\t-----------------------------------------------------------------------------------------");
		printf("\n\t\tID\tCompany\tName\tLastname\tEmail\tContact\tAccount\tDiscount");
		printf("\n\t\t-----------------------------------------------------------------------------------------");
		while ((fread(&v, sizeof(v), 1, fp)) != 0)
		{
			printf("\n\t\t%d\t%s\t%s\t%s\t%s\t%s\t%s\t%.2f", v.vendor_id, v.company, v.name, v.lastname, v.email, v.contactNo, v.accountNo, v.discount);
		}
		printf("\n\t\t-----------------------------------------------------------------------------------------");
	}
	fclose(fp);
}


int find_vendor_by_id(int id, vendor_t *vend)
{
	FILE *fp;
	vendor_t v;
	fp = fopen("vendor.dat", "rb");
	if (fp == NULL)
	{
		return id;
	}
	else
	{
		while (fread(&v, sizeof(v), 1, fp) != 0)
		{
			if (id == v.vendor_id)
			{
				*vend = v;
			}
		}
	}
	fclose(fp);
	return id;
}

int last_vendor_id() //collect last vendor id , auto generated id
{
	FILE *fp;
	int id = 0;
	vendor_t  a;
	int size;
	size = sizeof(a);
	fp = fopen("vendor.dat", "rb");
	if (fp == NULL)
	{
		return 0;
	}
	else
	{
		fseek(fp, -size, SEEK_END);
		fread(&a, sizeof(a), 1, fp);
		id = a.vendor_id;
	}
	return id;
}



















































