#include "../../../include/common/uthash.h"
#include "../../../include/common/common.h"
#include "string.h"
#include "stdio.h"


/*
 * uthash.c
 * by: Elaine Wan
 * 
 * sandbox for exploring uthash functions:
 *  - hash struct
 *  - add_item
 *  - find_item
 * 
 * to run: clang -Wall uthash.c -o uthash
 */


/* --------- DEFINITIONS --------- */

#define ID_SIZE 20

typedef enum namespace { 
    action, 
    object, 
    npc, 
    dialogue 
} namespace_t;

/*
 * hash struct
 * for simplicity's sake, using id as key for now
 */
typedef struct hash {
    namespace_t n; // category, e.g. "npc"
    char *id; // item id, e.g. "villager"
    int *obj; // dummy ptr to actual object
    UT_hash_handle hh;
} hash_t; 


/*
 * compound key struct
 * essentially, a wrapper for id and namespace_t
 */
typedef struct cmpkey {
    char id[ID_SIZE]; // item id, e.g. "villager"
    namespace_t n; // category, e.g. "npc"
 } cmpkey_t;

/*
 * hash struct with compound key
 * cmpkey struct as key
 */
typedef struct cmphash {
    cmpkey_t key;
    int *obj; // dummy ptr to actual object
    UT_hash_handle hh;
} cmphash_t; 


/* ------ SIMPLE HASH FUNCTIONS ------ */

/* 
 * find_item - finds item in hash table
 * 
 * Parameters:
 *  **t: double ptr to hash table
 *  *newid: key string (used for search)
 * 
 * Returns:
 *  ptr to item (NULL if none found)
 */
hash_t *find_item(hash_t **t, char *newid) 
{
    hash_t *res;
    HASH_FIND_STR(*t, newid, res);
    return res;
}

/* 
 * add_item - allocates space for and adds item to hash table
 * 
 * Parameters:
 *  **t: double ptr to hash table
 *  name: enum denoting category
 *  *newid: string for new key
 * 
 * Returns:
 *  SUCCESS on completion
 */
int add_item(hash_t **t, namespace_t name, char *newid, int *o)
{
    hash_t *new = find_item(t, newid); // see if key already exists in hash
    if (new == NULL) {
        new = malloc(sizeof(hash_t));
        new->n = name;
        new->id = malloc(sizeof(char) * (strlen(newid) + 1));
        HASH_ADD_KEYPTR(hh, *t, newid, strlen(newid), new);
    }
    strcpy(new->id, newid);
    printf("%d, %s\n", new->n, new->id);
    return SUCCESS;
}

/* print_hash - prints all items in hash
 * 
 * Parameters:
 *  **t: double ptr to hash table
 * 
 * Returns: none
 * 
 */
void print_hash(hash_t **t)
{
    hash_t *i;
    for (i = *t; i != NULL; i = i->hh.next)
    {
        printf("namespace_t: %d, id: %s\n", i->n, i->id);
    }
    if (*t == NULL)
        printf("NULL\n");
}

/* free_hash - deletes & frees hash table
 * 
 * Parameters:
 *  **t: double ptr to hash table
 * 
 * Returns: SUCCESS if hash freed complete, FAILURE if **t == NULL
 */
void free_hash(hash_t **t)
{
    if (t == NULL)
        return FAILURE;
    hash_t *curr, *tmp;
    HASH_ITER(hh, *t, curr, tmp)
    {
        HASH_DEL(*t, curr);
        free(curr->id);
        free(curr);
    }
    return SUCCESS;
}


/* ------ COMPOUND HASH FUNCTIONS ------ */

/* find_cmp - finds item in hash table with struct as key
 * 
 * Parameters:
 *  **h: double ptr to hash table of cmphash_t type
 *  *newid: key string (used for search)
 *  name: indicates namespace_t (used for search)
 * 
 * Returns:
 *  ptr to item (NULL if none found)
 */
cmphash_t *find_cmp(cmphash_t **h, namespace_t name, char *newid)
{
    cmphash_t *res;
    cmpkey_t tmp;
    memset(&tmp, 0, sizeof(tmp));
    strcpy(tmp.id, newid);
    tmp.n = name;

    HASH_FIND(hh, *h, &tmp, sizeof(cmpkey_t), res);

    return res;
}

/* add_cmp - allocates space for and adds item to cmphash_t table
 * 
 * Parameters:
 *  **h: double ptr to hash table
 *  name: enum denoting category
 *  *newid: string for new key
 *  *o: ptr to "object"
 * 
 * Returns:
 *  SUCCESS on completion
 */
int add_cmp(cmphash_t **h, namespace_t name, char *newid, int *o)
{
    cmphash_t *new = find_cmp(h, name, newid); // see if key already exists in hash
    if (new == NULL) {
        new = calloc(1, sizeof(cmphash_t));
        new->key.n = name;
        strcpy(new->key.id, newid);
        new->obj = o;

        HASH_ADD(hh, *h, key, sizeof(cmpkey_t), new);
    }
    new->obj = o;
    return SUCCESS;
}

/* free_cmp - deletes & frees hash table
 * 
 * Parameters:
 *  **h: double ptr to cmphash_t table
 * 
 * Returns: SUCCESS if hash table deleted & items freed, else FAILURE
 */
int free_cmp(cmphash_t **h)
{
    if (h == NULL)
        return FAILURE;
    cmphash_t *curr, *tmp;
    HASH_ITER(hh, *h, curr, tmp)
    {
        HASH_DEL(*h, curr);
        free(curr);
    }
    return SUCCESS;
}

/* print_cmp -  prints all items in cmphash_t
 * 
 * Parameters:
 *  **h: double ptr to hash table
 * 
 * Returns: none
 */
void print_cmp(cmphash_t **h)
{
    cmphash_t *i;
    for (i = *h; i != NULL; i = i->hh.next)
    {
        printf("namespace_t: %d, id: %s, obj: %d\n", i->key.n, i->key.id, *i->obj);
    }
    if (*h == NULL)
        printf("NULL\n");
}


int main()
{
    // declare hash
    hash_t *test = NULL;
    int x = 6;

    // test add_item
    printf("\nadd_item tests\n");
    add_item(&test, 2, "villager", &x);
    add_item(&test, 0, "LOOK", &x);
    print_hash(&test);
    
    // test find_item
    printf("\nfind_item tests\n");
    hash_t *find = find_item(&test, "villager");
    print_hash(&find);
    find = find_item(&test, "hello");
    print_hash(&find);

    // test free_hash
    printf("\nfree_hash tests\n");
    free_hash(&test);
    find = find_item(&test, "LOOK");
    if (find == NULL)
    {
        printf("free success!\n");
    }
    
    // test cmphash_t
    cmphash_t *test_cmp = NULL;

    // test add_cmp
    printf("\nadd_cmp tests\n");
    add_cmp(&test_cmp, 1, "TABLE", &x);
    add_cmp(&test_cmp, 1, "CHAIR", &x);
    print_cmp(&test_cmp);
    
    // test find_cmp
    printf("\nfind_cmp tests\n");
    cmphash_t *res = find_cmp(&test_cmp, 1, "TABLE");
    print_cmp(&res);
    res = find_cmp(&test_cmp, 0, "LOOK"); // ret NULL
    print_cmp(&res);
    res = find_cmp(&test_cmp, 1, "CHAIR");
    print_cmp(&res);

    free_cmp(&test_cmp);

    return 0;
}