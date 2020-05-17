#include "../../../include/common/uthash.h"
#include "../../../include/common/common.h"
#include "string.h"
#include "stdio.h"

/*
 * uthash.c
 * by: Elaine Wan
 * 
 * sandbox for exploring uthash functions:
 *  - hash type
 *  - add_item
 *  - find_item
 * 
 */

enum Namespace { action, object, npc, dialogue };

typedef struct objstore_test {
    enum Namespace n; // category, e.g. "npc"
    char *id; // item id, e.g. "villager"
    UT_hash_handle hh;
} test_t; // hash w/ key namespace, id

// for simplicity's sake (and getting familiar with uthash), using id as key for now

/* 
 * add_item
 * 
 * allocates space for and adds item to hash table
 * 
 * Parameters:
 *  **t: double ptr to hash table
 *  name: enum denoting category
 *  *newid: string for new key
 * 
 * Returns:
 *  SUCCESS on completion
 */
int add_item(test_t **t, enum Namespace name, char *newid)
{
    test_t *o;
    HASH_FIND_STR(*t, newid, o); // tests to see if key already exists in hash
    if (o == NULL) {
        o = malloc(sizeof(test_t));
        o->n = name;
        o->id = (char *)malloc(sizeof(&newid));
        HASH_ADD_KEYPTR(hh, *t, newid, strlen(newid), o);
    }
    strcpy(o->id, newid);
    printf("%d, %s\n", o->n, o->id);
    return SUCCESS;
}

/* find_item

 * finds item in hash table
 * 
 * Parameters:
 *  **t: double ptr to hash table
 *  *newid: key string (used for search)
 * 
 * Returns:
 *  ptr to item (NULL if none found)
 */
test_t *find_item(test_t **t, char *newid) 
{
    test_t *res;
    HASH_FIND_STR(*t, newid, res);
    return res;
}

/* print_hash
 *
 * prints all items in hash
 * 
 * Parameters:
 *  **t: double ptr to hash table
 * 
 * Returns: none - printed
 */
void print_hash(test_t **t)
{
    test_t *i;
    for (i = *t; i != NULL; i = i->hh.next)
    {
        printf("namespace: %d, id: %s\n", i->n, i->id);
    }
}

/* free_hash
 *
 * deletes & frees hash table
 * 
 * Parameters:
 *  **t: double ptr to hash table
 * 
 * Returns: none - hash table deleted & items freed
 */
void free_hash(test_t **t)
{
    test_t *curr, *tmp;
    HASH_ITER(hh, *t, curr, tmp)
    {
        HASH_DEL(*t, curr);
        free(curr->id);
        free(curr);
    }
}



int main()
{
    // declare hash
    test_t *test = NULL;

    // test add_item
    add_item(&test, 2, "villager");
    add_item(&test, 0, "LOOK");
    print_hash(&test);
    
    // test find_item
    test_t *find = find_item(&test, "villager");
    if (find == NULL)
    {
        printf("find failed :(\n");
    }
    else
    {
        printf("find result: %s\n", find->id);

    }

    // test free_hash
    free_hash(&test);
    find = find_item(&test, "LOOK");
    if (find == NULL)
    {
        printf("free success!\n");
    }
    

    return 0;
}