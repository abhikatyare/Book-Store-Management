#ifndef __VENDOR_H
#define __VENDOR_H

typedef struct Vendor
{
	int vendor_id;
	char company[60];
	char name[60];
	char lastname[60];
	char email[60];
	char contactNo[60];
	char accountNo[60];
	float discount;
}vendor_t;

void write_vendor_in_file(vendor_t *cust);
void read_vendor_from_file();
int last_vendor_id();
int find_vendor_by_id(int id, vendor_t *vend);

#endif