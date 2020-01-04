#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
 * Utilities for manipulating bytes, arrays and working with datatypes.
*/

typedef unsigned char* byte_pointer;

void show_bytes(byte_pointer start, size_t len) {
	int i;
	for(i = 0; i < len; i++)
		printf(" %.2x", start[i]);
	printf("\n");
}

void show_int(int x) {
	printf("Integer: "); show_bytes((byte_pointer) &x, sizeof(int));
}

void show_float(float x) {
	printf("Float:   "); show_bytes((byte_pointer) &x, sizeof(float));
}

void show_pointer(void* x) {
	printf("Pointer: "); show_bytes((byte_pointer) &x, sizeof(void*));
}

int hex_to_binary(char hex[], int binary_number[]) {
	int i, j=0, length, decimal=0;
	//initialize length traversing the hex char array until \0 is found
	for(length=0; hex[length]!='\0'; ++length);

	printf("\nCalculations...\n");	
	//loop until the end of the hex char array 
	for(i=0; hex[i]!='\0'; ++i, --length) {
		//use ascii codes to subtract the correct amount times base 16 to the (length of hex - 1), decreasing length in each iter
		if(hex[i]>='0' && hex[i]<='9')
			decimal+=(hex[i]-'0')*pow(16,length-1);
		if(hex[i]>='A' && hex[i]<='F')
			decimal+=(hex[i]-55)*pow(16,length-1);
		if(hex[i]>='a' && hex[i]<='f')
			decimal+=(hex[i]-87)*pow(16,length-1);
	}
	//variable decimal contains the hexadecimal number in decimal format. 
	while (decimal != 0) {
		binary_number[j++] = decimal%2;
		decimal /= 2;
	}
	return j;
}

void inplace_swap(int* x, int* y) {
	*y = *x ^ *y;
	*x = *x ^ *y;
	*y = *x ^ *y;
}

void reverse_array(int a[], int cnt) {
	int first, last;
	for(first = 0, last = cnt - 1; first <= last; first++, last--) {
		// for cnt = 2k + 1 (array containing an odd number of integers)
		// we cannot perform the swap operation for the median value.
		// hence when the two values are the same, we do not perform the swap
		if(a[first] == a[last])
			continue;
		inplace_swap(&a[first], &a[last]);
	}
}
