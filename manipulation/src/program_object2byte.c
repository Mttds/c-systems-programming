#include <stdio.h>

/*
 * Converts an integer to its byte (hexadecimal pattern) representation.
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

void test_show_bytes(int val) {
	int ival = val;
	float fval = (float)ival;
	int* pval = &ival;
	show_int(ival);
	show_float(fval);
	show_pointer(pval);
}

int main() {
	printf("******** Program Object to hexadecimal converter ********\n");
	int i;
	printf("Enter an integer value to retrieve its byte representation: ");
	scanf("%d", &i);

	test_show_bytes(i);
	return 0;
}	
