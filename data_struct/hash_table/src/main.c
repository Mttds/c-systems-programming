#include <stdio.h>
#include "hash_table.h"

/* Compile with -lm option (gcc -o <file.exe> <file.c> -lm) to link the math.h library included in prime_number.h */

int main() {
	hsh_tbl* ht = hsh_tbl_new();

	printf("Inserting elements into the hash table...\n");
	hsh_tbl_insert(ht, "abc", "2");
	hsh_tbl_insert(ht, "dfg", "3");
	char* seek_abc = hsh_tbl_search(ht, "abc");
	printf("Looking for key 'abc' in the hash table. Hashed value found: %s\n", seek_abc);

	printf("Updating key 'abc' with value 9...\n");
	hsh_tbl_update(ht, "abc", "9");
	seek_abc = hsh_tbl_search(ht, "abc");
	printf("Looking for key 'abc' in the hash table. Hashed value found: %s\n", seek_abc);

	char* seek_dfg = NULL;
	seek_dfg = hsh_tbl_search(ht, "dfg");
	printf("Looking for key 'dfg' in the hash table. Hashed value found: %s\n", seek_dfg);

	printf("Deleting element with key 'dfg'...\n");
	hsh_tbl_delete(ht, "dfg");

	seek_dfg = hsh_tbl_search(ht, "dfg");
	printf("Looking for key 'dfg' in the hash table. Hashed value found: %s\n", seek_dfg);

	printf("Inserting element with key '123'...\n");
	hsh_tbl_insert(ht, "123", "h");

	show_hash_table(ht);

	hsh_tbl_del(ht);
	//show_hash_table(ht); //causes a segmentation fault. To check
	return 0;
}
