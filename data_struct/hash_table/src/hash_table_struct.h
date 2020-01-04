#ifndef HASH_TABLE_STRUCT
#define HASH_TABLE_STRUCT

typedef struct {
	char* key;
	char* value;
} hsh_tbl_elmnt;

typedef struct {
	int base_size;
	int size;
	int count;
	hsh_tbl_elmnt** elements;
} hsh_tbl;

/*API:
 * insert: hsh_tbl_insert
 * search: hsh_tbl_search
 * delete: hsh_tbl_delete
 * update: hsh_tbl_update
*/
/**********************************************************************/
void hsh_tbl_insert(hsh_tbl* ht, const char* key, const char* value);
char* hsh_tbl_search(hsh_tbl* ht, const char* key);
void hsh_tbl_delete(hsh_tbl* ht, const char* key);
void hsh_tbl_update(hsh_tbl* ht, const char* key, const char* value);
/**********************************************************************/

#endif
