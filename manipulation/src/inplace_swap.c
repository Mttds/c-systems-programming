#include <stdio.h>
#include <stdlib.h>

/*
 * Uses a boolean ring where the ^ operator corresponds to the arithmetic addition inverse
 * such that x + -x = 0. The ^ operation is a bit-level operation which applies the xor logical condition.
 * a ^ a = 0 holds true for every value of a. (i.e every element is its own additive inverse)
 * With this technique we can swap two values without using a temporary variable. 
*/

void inplace_swap(int* x, int* y) {
	printf("Executing in-place swap of x=%d and y=%d\n", *x, *y);
	*y = *x ^ *y;
	*x = *x ^ *y;
	*y = *x ^ *y;
	//Dereferencing pointers to print the value
	printf("Swapped the values: x=%d and y=%d\n", *x, *y);
}

int main() {
	/* declare and allocate the integer pointers */
	int* x = malloc(sizeof(int));
	int* y = malloc(sizeof(int));

	printf("Input integer x: ");
	scanf("%d", x);
	printf("Input integer y: ");
	scanf("%d", y);

	inplace_swap(x, y);

	//free the allocated memory
	free(x);
	free(y);
	return 0;
}
