#include <stdlib.h>
#include <string.h>
#include "hash_table_struct.h"
#include "prime_number.h"

const int PRIME_1 = 163;
const int PRIME_2 = 199;
static hsh_tbl_elmnt NULL_ELEMENT = {NULL, NULL};
const int BASE_SIZE = 53;

static hsh_tbl_elmnt* hsh_tbl_elmnt_new(const char* k, const char* v) {
	hsh_tbl_elmnt* i = malloc(sizeof(hsh_tbl_elmnt));
	/* Access the elements of struct hsh_tbl_elmnt and duplicate the key and value strings */
	i->key = strdup(k);
	i->value = strdup(v);
	return i;
}

hsh_tbl* hsh_tbl_new_size(const int base_size) {
	/* Allocate memory for a new hsh_tbl struct and initialize the struct's elements */
	hsh_tbl* ht = malloc(sizeof(hsh_tbl));

	/* size and count are statically initialized for now */
	ht->base_size = base_size;
	ht->size = next_prime(ht->base_size);
	ht->count = 0;

	/* items is allocated with null bytes (i.e an array of null pointers hsh_tbl_elmnt** elements */
	ht->elements = calloc((size_t)ht->size, sizeof(hsh_tbl_elmnt*));
	return ht;
}

hsh_tbl* hsh_tbl_new() {
	return hsh_tbl_new_size(BASE_SIZE);
}

/* Functions to delete the allocated objects of type hsh_tbl_elmnt and hst_tbl */
static void hsh_tbl_del_elmnt(hsh_tbl_elmnt* i) {
	/* We free the memory of the char* before deleting the struct */
	free(i->key);
	free(i->value);
	if(i != NULL) //TO_DO: check freeing of invalid pointer abort 
		free(i);
}

void hsh_tbl_del(hsh_tbl* ht) {
	/* We cycle thru the hsh_tbl_elmnt pointers and use the previously defined function to free the memory allocated for hsh_tbl_elmnt* */
	for(int i = 0; i < ht->size; i++) {
		hsh_tbl_elmnt* element = ht->elements[i];
		if(element != NULL) {
			hsh_tbl_del_elmnt(element);
		}
	}
	/* Finally, we free the memory for hsh_tbl_elmnt** and hsh_tbl* as well */
	free(ht->elements);
	free(ht);
}

/* Resizing up or down our hash table if it gets too full or too empty by copying the data to another struct 
 * Functions resize_up and resize_down will be our helper functions called by the insert and delete API respectively.
 * If during a call to hsh_tbl_insert the load of the table is > 70% then we resize it up.
 * Likewise, if a call to hsh_tbl_delete calculates a load that is < 10% then we resize the hash table down.
*/
static void hsh_tbl_resize(hsh_tbl* ht, const int base_size) {
	if(base_size < BASE_SIZE)
		return;
	hsh_tbl* new_hsh_tbl = hsh_tbl_new_size(base_size);
	for(int i = 0; i < ht->size; i++) {
		hsh_tbl_elmnt* element = ht->elements[i];
		if(element != NULL && element != &NULL_ELEMENT) {
			hsh_tbl_insert(new_hsh_tbl, element->key, element->value);
		}
	}

	ht->base_size = new_hsh_tbl->base_size;
	ht->count = new_hsh_tbl->count;

	const int tmp_size = ht->size;
	ht->size = new_hsh_tbl->size;
	new_hsh_tbl->size = tmp_size;

	hsh_tbl_elmnt** tmp_elements = ht->elements;
	ht->elements = new_hsh_tbl->elements;
	new_hsh_tbl->elements = tmp_elements;

	hsh_tbl_del(new_hsh_tbl);
}

static void resize_up(hsh_tbl* ht) {
	const int new_size = ht->base_size * 2;
	hsh_tbl_resize(ht, new_size);
}

static void resize_down(hsh_tbl* ht) {
	const int new_size = ht->base_size / 2;
	hsh_tbl_resize(ht, new_size);
}

/* 
 * Hashing function:
 * Returns a number between 0 and m
 * 1. Convert the string to a long integer by multiplying each character (the ascii code at index i) by a^(length -(i+1))
 * 2. Reduce its size by taking the mod m
 * a should be a prime number having size greater than the possible set of characters used in char* s (i.e 128 ascii characters)
*/
static int hashing_func(const char* s, const int a, const int m) {
	long hash = 0;
	const int length = strlen(s);
	for(int i = 0; i < length; i++) {
		hash += (long)pow(a, length - (i+1)) * s[i];
		hash = hash % m;
	}
	return (int)hash;
}

/* The following function is defined to handle collisions for our hashing_func()
 * index = hash1(string) + i * (hash2(string) + 1) % buckets
 * If there is no collision, i = 0 and the function returns the result of our hashing_func()
 * We add 1 to our second hashing to exclude the possibility of the second term evaluating to 0 in which case our function would keep calling itself to resolve the collision
*/
static int get_hash(const char* s, const int buckets, const int i) {
	const int hash1 = hashing_func(s, PRIME_1, buckets);
	const int hash2 = hashing_func(s, PRIME_2, buckets);
	return (hash1 + i * (hash2 + 1)) % buckets;
}

/* API implementation */
/* Insertion:
 * Create a new hsh_tbl_elmnt pointer with function hsh_tbl_elmnt_new passing the declared key-value pair
 * Retrieve the index (0,m) with get_hash() using 0 as the number of attempts
 * Retrieve the current element at index from our hsh_tbl and set i to 1
 * if there is a collision (i.e the current element pointer is not NULL) then call get_hash() again with i++ until the current element pointer is NULL
 * Set the element at the last obtained index to the element created by hsh_tbl_elmnt_new with the key-value pair provided. Set the count variable in the hsh_tbl struct to count++
 * current_element != &NULL_ELEMENT is checked to take into account deleted elements with hsh_tbl_delete()
*/
void hsh_tbl_insert(hsh_tbl* ht, const char* key, const char* value) {
	const int load = ht->count * 100 / ht->size;
	if(load > 70)
		resize_up(ht);

	int i = 0;
	hsh_tbl_elmnt* element = hsh_tbl_elmnt_new(key, value);
	int index = get_hash(element->key, ht->size, i);
	hsh_tbl_elmnt* current_element = ht->elements[index];
	i = 1;
	while(current_element != NULL) {
		/* Handling already present key. We delete the current element and insert the new element simulating an update */
		if(current_element != &NULL_ELEMENT) {
			if(strcmp(current_element->key, key) == 0) {
				hsh_tbl_del_elmnt(current_element);
				ht->elements[index] = element;
				return;
			}
		}
		index = get_hash(element->key, ht->size, i);
		current_element = ht->elements[index];
		i++;
	}
	ht->elements[index] = element;
	ht->count++;
}

/* Search:
 * Our search function works similarly to hsh_tbl_insert, but we use strcmp (string compare) to evaluate the key of the current element with the one provided as input.
 * If there is a match, we return the value from the struct of the currente element, otherwise we keep searching until the element has a NULL pointer meaning our hash table is empty.
 * If no match is found, NULL is returned.
 * element != &NULL_ELEMENT takes into account deleted elements by hsh_tbl_delete (different from element != NULL since our pointer to hsh_tbl_elmnt is initialized)
*/
char* hsh_tbl_search(hsh_tbl* ht, const char* key) {
	int i = 0;
	int index = get_hash(key, ht->size, i);
	hsh_tbl_elmnt* element = ht->elements[index];
	i = 1;
	while(element != NULL) {
		if(element != &NULL_ELEMENT && strcmp(element->key, key) == 0) {
			return element->value;
		}
		index = get_hash(key, ht->size, i);
		element = ht->elements[index];
		i++;
	}
	return NULL;
}

/* Deletion:
 * We define a NULL hsh_tbl_elmnt with the static variable NULL_ELEMENT. Like we did for insertion and searches, we loop thru the hash table
 * and if the currente element is not a NULL_ELEMENT and the input key matches with that of the current element, we set the element at the current
 * index in our hash table to a NULL_ELEMENT.
 * Finally, we decrement the count variable of our hash_table when we are done traversing the table.
*/
void hsh_tbl_delete(hsh_tbl* ht, const char* key) {
	const int load = ht->count * 100 / ht->size;
	if(load < 10)
		resize_down(ht);

	int i = 0;
	int index = get_hash(key, ht->size, i);
	hsh_tbl_elmnt* element = ht->elements[index];
	i = 1;
	while(element != NULL) {
		if (element != &NULL_ELEMENT && strcmp(element->key, key) == 0) {
			hsh_tbl_del_elmnt(element);
			ht->elements[index] = &NULL_ELEMENT;
		}
		index = get_hash(key, ht->size, i);
		element = ht->elements[index];
		i++;
	}
	ht->count--;
}

/* Update:
 * We use hsh_tbl_delete to delete the element at the input key and hsh_tbl_insert to insert the new element (with it's new value) at the same key.
 * Doing this we simulate an update with a delete+insert operation.
*/
void hsh_tbl_update(hsh_tbl* ht, const char* key, const char* value) {
	hsh_tbl_delete(ht, key);
	hsh_tbl_insert(ht, key, value);
}

/* Printing function */
void show_hash_table(hsh_tbl* ht) {
	if(ht == NULL) {
		printf("The input hash table points to a null address.\n");
		return;
	}

	printf("*** Printing hash table content ***\n");
	printf("The table has %d elements.\n", ht->count);
	for(int i = 0; i < ht->size; i++) {
		hsh_tbl_elmnt* element = ht->elements[i];
		if(element != NULL && element != &NULL_ELEMENT)
			printf("Element at index %d with key %s and value %s\n", i, element->key, element->value);

	}
}
