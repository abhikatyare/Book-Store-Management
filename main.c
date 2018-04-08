#include<stdio.h>
#include<stdlib.h>
#include"item.h"
#include"porder.h"
#include"customer.h"
#include"vendor.h"
#include "list.h"
#include"bill.h"
enum main{ EXIT = 0, MAN_CUST1, MAN_PUR1, MAN_ITM1, MAN_SAL };

int main_menu()
{
	int choice;
	printf("\n\t\t0.Exit\n\t\t1.Manage Customer\n\t\t2.Manage Purchase Order\n\t\t3.Manage Items\n\t\t4.Manage Sale");
	printf("\n\n\t\tEnter the Choice::");
	scanf("%d", &choice);
	return choice;
}

enum man_cust{ ADD_CUST = 1, MAN_CUST };

int sub_cust()
{
	int choice;
	printf("\n\t\t1.Add New Customer\n\t\t2.Customer Manager");
	printf("\n\n\t\tEnter the Choice::");
	scanf("%d", &choice);
	return choice;
}

enum man_cust1{ VIEW_CUST = 1 };

int sub_cust1()
{
	int choice;
	printf("\n\t\t1.View Customer");
	printf("\n\n\t\tEnter the Choice::");
	scanf("%d", &choice);
	return choice;
}





enum man_ven{ ADD_VEN = 1, MAN_VEN, MAN_PUR };

int sub_ven()
{
	int choice;
	printf("\n\t\t1.Add New Vendor\n\t\t2.Vendor Manager\n\t\t3.Purchase Order Manager");
	printf("\n\n\t\tEnter the Choice::");
	scanf("%d", &choice);
	return choice;
}

enum man_ven1{ VIEW_VEN = 1 };

int sub_ven1()
{
	int choice;
	printf("\n\t\t1.View Vendor");
	printf("\n\n\t\tEnter the Choice::");
	scanf("%d", &choice);
	return choice;
}

enum man_ven2{ ADD_PUR=1, VIEW_PUR };

int sub_ven2()
{
	int choice;
	printf("\n\t\t1.Add Purchase Order\n\t\t2.View Purchase Order");
	printf("\n\n\t\tEnter the Choice::");
	scanf("%d", &choice);
	return choice;
}



enum man_itm{ ADD_ITM = 1, MAN_ITM };

int sub_itm()
{
	int choice;
	printf("\n\t\t1.Add New Item\n\t\t2.Item Manager");
	printf("\n\n\t\tEnter the Choice::");
	scanf("%d", &choice);
	return choice;
}

enum man_itm1{ VIEW_ITM = 1 };

int sub_itm1()
{
	int choice;
	printf("\n\t\t1.View Item");
	printf("\n\n\t\tEnter the Choice::");
	scanf("%d", &choice);
	return choice;
}





enum man_sal{ SAL_ITM = 1, BILL, PREV_BILL };

int sub_sal()
{
	int choice;
	printf("\n\t\t1.Sale Item\n\t\t2.Generate Bill\n\t\t3.Previous Bill\n");
	printf("\n\n\t\tEnter the Choice::");
	scanf("%d", &choice);
	return choice;
}

enum man_sal1{ CHECK = 1 };

int sub_sal1()
{
	int choice;
	printf("\n\t\t1.Check Availability");
	printf("\n\n\t\tEnter the Choice::");
	scanf("%d", &choice);
	return choice;
}


void function_for_man_cust()
{
	customer_t c;
	int mc, mc1;
	do{
		mc = sub_cust();
		switch (mc)
		{
		case ADD_CUST:
			system("cls");
			write_customer_in_file(&c);
			getchar();
			getchar();
			break;
		case MAN_CUST:
			do{
				mc1 = sub_cust1();
				switch (mc1)
				{
				case VIEW_CUST:
					system("cls");
					read_customer_from_file();
					getchar();
					getchar();
					break;
				}
			} while (mc1 != 0);
			break;
		}
	} while (mc != 0);
}


void function_for_man_ven()
{
	vendor_t v;
	porder_t po;
	int mv, mv1,mp;
	do{
		mv = sub_ven();
		switch (mv)
		{
		case ADD_VEN:
			system("cls");
			write_vendor_in_file(&v);
			getchar();
			getchar();
			break;
		case MAN_VEN:
			do
			{
				mv1 = sub_ven1();
				switch (mv1)
				{
				case VIEW_VEN:
					system("cls");
					read_vendor_from_file();
					getchar();
					getchar();
					break;
				}
			} while (mv1 != 0);
			break;
		case MAN_PUR:
			do
			{
				mp = sub_ven2();
				switch (mp)
				{
				case ADD_PUR:
					system("cls");
					write_porder_in_file(&po);
					getchar();
					getchar();
					break;
				case VIEW_PUR:
					system("cls");
					read_porder_from_file();
					getchar();
					getchar();
					break;
				}
			} while (mp != 0);
			break;
		}
	} while (mv != 0);
}


void function_for_man_itm(list_t *l)
{
	item_t itm;
	int mi, mi1;
	getchar();
	do{
		mi = sub_itm();
		switch (mi)
		{
		case ADD_ITM:
			system("cls");
			write_item_in_file(&itm,l);
			getchar();
			getchar();
			printf("\nItem ADDED");
			break;
		case MAN_ITM:
			do
			{
				mi1 = sub_itm1();
				switch (mi1)
				{
				case VIEW_ITM:
					system("cls");
					display_list(l);
					getchar();
					getchar();
					break;
				}
			} while (mi1 != 0);
			break;
		}
	} while (mi != 0);
}



void function_for_man_sal(list_t *l,list_t *cart_list)
{
	int ms;
	bill_t b;
	char pname[20];
	do{
		ms = sub_sal();
		switch (ms)
		{
		
		case SAL_ITM:
			system("cls");
			printf("In Sale Item Display\n");
			display_list(l);
			printf("\nEnter the Product::");
			scanf("%s",pname);
			find_item_in_list(pname,l,cart_list);
			display_list(cart_list);
			getchar();
			getchar();
			break;
		case BILL:
			system("cls");
			printf("\nThis is the BILL");
			generate_bill(&b, cart_list);
			getchar();
			getchar();
			break;
		case PREV_BILL:
			system("cls");
			read_bill_from_file();
			break;
		}
	} while (ms != 0);
}



int main()
{
	int ch;
	list_t l,cart_list;
	init_head(&cart_list);
	init_head(&l);
	load_item_from_stock_to_link_list(&l);
	do{
		ch = main_menu();
		switch (ch)
		{
		case EXIT:
			break;



		case MAN_CUST1:
			system("cls");
			function_for_man_cust();
			system("cls");
			break;



		case MAN_PUR1:
			system("cls");
			function_for_man_ven();
			system("cls");
			break;


		case MAN_ITM1:
			system("cls");
			function_for_man_itm(&l);
			system("cls");
			break;



		case MAN_SAL:
			system("cls");
			function_for_man_sal(&l,&cart_list);
			system("cls");
			break;
		}
		write_form_link_list_to_stock(&l);
	} while (ch != 0);

	return 0;
}

