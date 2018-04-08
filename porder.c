#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"vendor.h"
#include"porder.h"





int last_po_id() // auto generated po_id
{

	FILE *fp;
	int id = 0;
	porder_t p;
	int size;
	size = sizeof(p);
	fp = fopen("order.dat", "rb");
	if (fp == NULL)
	{
		return 0;
	}
	else
	{
		if (fseek(fp, -size, SEEK_END) == -1)
			return 0;
		fseek(fp, -size, SEEK_END);
		fread(&p, sizeof(p), 1, fp);
		id = p.po_id;
		fclose(fp);
	}

	return id;
}

void input_porder(porder_t *po)
{
	vendor_t v;
	int vid;
	po->po_id = last_po_id() + 1;
	printf("\n\t\tEnter Vendor Id			::");
	scanf("%d", &po->vendor_id);
	printf("\t\tEnter the Product Name		::");
	scanf("%s", po->item.product_Name);
	printf("\t\tEnter the Product Description	::");
	scanf("%s", po->item.product_Description);
	printf("\t\tEnter the Quantity		::");
	scanf("%d", &po->item.quantity);
	printf("\t\tEnter the Unit Price		::");
	scanf("%f", &po->item.unit_price);
	vid = find_vendor_by_id(po->vendor_id, &v);
	printf("\n\t\t---------------------------------------");
	printf("\n\t\t\t\t\tDiscount::%.2f", v.discount);
	printf("\n\t\t---------------------------------------");
	po->status = RAISED;
}

void write_porder_in_file(porder_t *po)
{
	FILE *fp;
	porder_t p;
	input_porder(&p);
	fp = fopen("order.dat", "ab");
	if (fp == NULL)
	{
		return;
	}
	else
	{
		fwrite(&p, sizeof(p), 1, fp);
	}
	fclose(fp);
}

void display_porder(porder_t *po)
{
	vendor_t v;
	int vid;
	float total,dis_unit;
	char cname[20];
	vid = find_vendor_by_id(po->vendor_id, &v);
	strcpy(cname, v.company);
	dis_unit = po->item.unit_price - (po->item.unit_price*(v.discount / 100));
	total = po->item.quantity*dis_unit;
	printf("\n%d", po->po_id);
	printf("\t%s", po->item.product_Name);
	printf("\t\t%s", po->item.product_Description);
	printf("\t%d", po->item.quantity);
	printf("\t\t%.2f", po->item.unit_price);
	printf("\t\t%s", v.company);
	printf("\t%.2f", v.discount);
	printf("\t%.2f", total);
	printf("\t\t%.2f", dis_unit);
	printf("\t\t%d", po->status);
}


void read_porder_from_file()
{
	FILE *fp;
	porder_t p;
	fp = fopen("order.dat", "rb");
	if (fp == NULL)
	{
		return;
	}
	else
	{
		printf("\n-------------------------------------------------------------------------------------------------------------------------");
		printf("\nPo_Id\tPro_Name\tPro_Des\tQuantity\tUnit_Price\tCompany\tDis\tDis_Total\tDis_Price\tStatus");
		printf("\n-------------------------------------------------------------------------------------------------------------------------");

		while (fread(&p, sizeof(p), 1, fp) != 0)//read file till EOF
		{
			display_porder(&p);//Display the file contents one after another
		}
		printf("\n------------------------------------------------------------------------------------------------------------------------\n");
	}
	fclose(fp);
}




int find_purchase_order_by_name(char *purchase, porder_t *po_out)
{
	FILE *fp;
	porder_t p;
	int flag = 0;
	fp = fopen("order.dat", "rb");
	if (fp == NULL)
	{
		return flag;
	}
	else
	{
		while (fread(&p, sizeof(p), 1, fp) != 0)
		{
			if (strcmp(purchase, p.item.product_Name) == 0 && p.status==0)
			{
				*po_out = p;
				flag = 1;
			}
		}
	}
	if (flag == 0)
		printf("\nProduct Not Found");
	fclose(fp);
	return flag;
}
