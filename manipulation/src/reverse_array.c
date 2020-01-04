#include <stdio.h>
#include <stdlib.h>
#include "../lib/common_func.h"
#define MAX_SIZE 100

/*
 * Reversing an array using inplace_swap
 * Compile it with gcc -lm -o reverse_array.exe reverse_array.c to link the math.h library included in common_func.h
*/

int main() {

	int cnt;
	int array_i [MAX_SIZE];

	printf("Enter the array size: ");
	scanf("%d", &cnt);
	printf("Enter the elements of the integer array: \n");
	for(int i=0; i < cnt; i++)
		scanf("%d", &array_i[i]);

	reverse_array(array_i, cnt);

	for(int j=0; j < cnt; j++)
	    printf("Element at %d is: %d\n", j, array_i[j]);

	return 0;
}
