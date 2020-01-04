#include <math.h>
#include "prime_number_interface.h"

/* Excape conditions @ x < 2, x < 4, and when x is a multiple of 2 */
int is_prime(const int i) {
	if(i < 2)
		return -1;
	if(i < 4)
		return 1; // prime when i is 2 or 3
	if((i % 2) == 0)
		return 0;

	/* Loop from 3 to the nearest square root for j (and increase by 2 for an odd number). If the loop ends, i is prime */
	for(int j = 3; j <= floor(sqrt((double)j)); j += 2) {
		if((i % j) == 0)
			return 0;
	}
	return 1;
}

/* Keep calling func is_prime until it returns 1 (i.e a prime number is found) */
int next_prime(int i) {
	while(is_prime(i) != 1) {
		i++;
	}
	return i;
}
