/* Implementations of the item struct */
#include <string.h>

#include "game-state/item.h"
#include "game-state/game_action.h"
#include "cli/util.h"


// BASIC ITEM FUNCTIONS -------------------------------------------------------
/* see common-item.h*/
int item_init(item_t *new_item, char *item_id, char *short_desc,
              char *long_desc)
{

    assert(new_item != NULL);
    strcpy(new_item->item_id, item_id);
    case_insensitize(new_item->item_id);
    strcpy(new_item->short_desc, short_desc);
    strcpy(new_item->long_desc, long_desc);
    new_item->stat_effects = NULL;

    return SUCCESS;
}

/* see item.h */
item_t *item_new(char *item_id, char *short_desc, char *long_desc)
{
    item_t *new_item = malloc(sizeof(item_t));
    memset(new_item, 0, sizeof(item_t));

    item_id = case_insensitized_string(item_id);

    new_item->item_id = malloc(MAX_ID_LEN * sizeof(char)); // tentative size allocation
    new_item->short_desc = malloc(MAX_SDESC_LEN * sizeof(char));
    new_item->long_desc = malloc(MAX_LDESC_LEN * sizeof(char));

    int check = item_init(new_item, item_id, short_desc, long_desc);

    if (new_item == NULL || new_item->item_id == NULL ||
            new_item->short_desc == NULL || new_item->long_desc == NULL)
    {

        return NULL; //item struct not properly malloced

    }

    if(check != SUCCESS)
    {
        return NULL;
    }

    return new_item;

}

/* see item.h */
char *get_sdesc_item(item_t *item)
{
    if (item == NULL)
    {
        return NULL;
    }
    return item->short_desc;
}

/* see item.h */
char *get_ldesc_item(item_t *item)
{
    if (item == NULL)
    {
        return NULL;
    }
    return item->long_desc;
}

/* See item.h */
int add_item_to_hash(item_hash_t **ht, item_t *new_item)
{
    item_t *check, *itr;
    
    HASH_FIND(hh, *ht, new_item->item_id, strnlen(new_item->item_id, MAX_ID_LEN), check);
    
    LL_FOREACH(check, itr)
    {
        if (itr == new_item)
        {
            /* Same memory address */
            return FAILURE;
        }
    }

    if (check != NULL)
    {
        /* Same item id, not same memory address */
        HASH_DEL(*ht, check);
        new_item->next = check;
    }
    
    HASH_ADD_KEYPTR(hh, *ht, new_item->item_id, strnlen(new_item->item_id, MAX_ID_LEN),
                    new_item);

    return SUCCESS;
}

/* See item.h */
item_list_t *get_all_items_in_hash(item_hash_t **ht)
{
    item_list_t *head = NULL;
    item_t *ITTMP_ITEMRM, *curr_item, *dup_item;
    item_list_t *tmp;
    
    HASH_ITER(hh, *ht, curr_item, ITTMP_ITEMRM)
    {
        /* If item id has no duplicates - only iterates once
         * If more than one identical id - iterates through all */
        LL_FOREACH(curr_item, dup_item)
        {
            tmp = malloc(sizeof(item_list_t));
            tmp->item = dup_item;
            LL_APPEND(head, tmp);
        }
    }
    
    return head;
}

/* See item.h */
item_t *get_item_in_hash(item_hash_t *ht, char *id)
{
    item_t *item;

    HASH_FIND_STR(ht, id, item);

    return item;
}

/* See item.h */
int remove_item_from_hash(item_hash_t **ht, item_t *old_item)
{
    item_t *check;
    HASH_FIND(hh, *ht, old_item->item_id, strnlen(old_item->item_id, MAX_ID_LEN), check);
    
    // Only deletes if item exists in hashtable
    if (check != NULL)
    {
        if (check == old_item && old_item->next != NULL)
        {
            /* Multiple identical item ids;
             * item to delete is head of linked list */
            HASH_DELETE(hh, *ht, old_item);
	        add_item_to_hash(ht, old_item->next);
            old_item->next = NULL;
        }
        else if (check == old_item)
        {
            /* Item to delete is only item w/ id in hashtable */
            HASH_DELETE(hh, *ht, old_item);
        }
        else
        {
            item_t *prev, *curr;
            prev = check;
            curr = check->next;
            while (curr != NULL)
            {
                if (curr == old_item)
                {
                    /* Multiple identical item ids;
                     * item to delete might be found later in linked list.
                     * Note that if same memory address is not found,
                     * no items will be removed */
                    prev->next = curr->next;
                    curr->next = NULL;
                }
                
                prev = prev->next;
                curr = curr->next;
            }
        }
    }
    
    return SUCCESS;
}

/* See item.h */
int add_item_to_all_items_hash(item_hash_t **all_items, item_t *item)
{
    item_t *check, *itr;
    
    HASH_FIND(hh_all_items, *all_items, item->item_id, 
              strnlen(item->item_id, MAX_ID_LEN), check);

    LL_FOREACH(check, itr)
    {
        if (itr == item)
        {
            /* Same memory address */
            return FAILURE;
        }
    }

    if (check != NULL)
    {
        /* Same item id, not same memory address */
        HASH_DELETE(hh_all_items, *all_items, check);
        item->next = check;
    }
    
    HASH_ADD_KEYPTR(hh_all_items, *all_items, item->item_id,
                    strnlen(item->item_id, MAX_ID_LEN), item);

    return SUCCESS;
}

/* See item.h */
int remove_item_from_all_items_hash(item_hash_t **all_items, item_t *item)
{
    item_t *check;
    HASH_FIND(hh_all_items, *all_items, item->item_id,
              strnlen(item->item_id, MAX_ID_LEN), check);

    // Only deletes if item exists in hashtable
    if (check != NULL)
    {
        if (check == item && item->next != NULL)
        {
            /* Multiple identical item ids;
             * item to delete is head of linked list */
            HASH_DELETE(hh_all_items, *all_items, item);
	        add_item_to_all_items_hash(all_items, item->next);
            item->next = NULL;
        }
        else if (check == item)
        {
            /* Item to delete is only item w/ id in hashtable */
            HASH_DELETE(hh_all_items, *all_items, item);
        }
        else
        {
            item_t *prev, *curr;
            prev = check;
            curr = check->next;
            while (curr != NULL)
            {
                if (curr == item)
                {
                    /* Multiple identical item ids;
                     * item to delete might be found later in linked list.
                     * Note that if same memory address is not found,
                     * no items will be removed */
                    prev->next = curr->next;
                    curr->next = NULL;
                }
                
                prev = prev->next;
                curr = curr->next;
            }
        }
    }
    
    return SUCCESS;
}

/* See item.h */
int add_effect_to_item(item_t *item, stat_effect_t *effect)
{
    stat_effect_t *check;
    HASH_FIND(hh, item->stat_effects, effect->key, 
              strlen(effect->key), check);

    if (check != NULL)
    {
        return FAILURE; //item already has the effect
    }

    HASH_ADD_KEYPTR(hh, item->stat_effects, effect->key, 
              strlen(effect->key), effect);
    return SUCCESS;
}

// ATTRIBUTE MANIPULATION FUNCTIONS -------------------------------------------
/* see common-item.h */
int add_attribute_to_hash(item_t* item, attribute_t* new_attribute)
{
    attribute_t* check;
    HASH_FIND(hh, item->attributes, new_attribute->attribute_key,
              strlen(new_attribute->attribute_key), check);
    if (check != NULL)
    {
        return FAILURE; //this attribute is already present.
    }
    HASH_ADD_KEYPTR(hh, item->attributes, new_attribute->attribute_key,
                    strlen(new_attribute->attribute_key), new_attribute);
    return SUCCESS;
}

/* see item.h */
attribute_t *get_attribute(item_t *item, char* attr_name)
{
    attribute_t* return_value;
    HASH_FIND(hh, item->attributes, attr_name, strlen(attr_name), return_value);

    return return_value;
}

// TYPE-SPECIFIC ATTRIBUTE INITIALIZING FUNCTIONS -------------------------------------------
/* see item.h */
attribute_t* str_attr_new(char* attr_name, char* value)
{
    attribute_t* new_attribute = malloc(sizeof(attribute_t));

    if (new_attribute == NULL) {
        fprintf(stderr, "Failed to allocate memory for new attribute");
        return NULL;
    }

    new_attribute->attribute_tag = STRING;
    new_attribute->attribute_value.str_val = value;
    new_attribute->attribute_key = strndup(attr_name, MAX_ID_LEN);

    return new_attribute;
}


/* see item.h */
attribute_t* int_attr_new(char* attr_name, int value)
{
    attribute_t* new_attribute = malloc(sizeof(attribute_t));

    if (new_attribute == NULL) {
        fprintf(stderr, "Failed to allocate memory for new attribute");
        return NULL;
    }

    new_attribute->attribute_tag = INTEGER;
    new_attribute->attribute_value.int_val = value;
    new_attribute->attribute_key = strndup(attr_name, MAX_ID_LEN);

    return new_attribute;
}


/* see item.h */
attribute_t* double_attr_new(char* attr_name, double value)
{
    attribute_t* new_attribute = malloc(sizeof(attribute_t));

    if (new_attribute == NULL) {
        fprintf(stderr, "Failed to allocate memory for new attribute");
        return NULL;
    }

    new_attribute->attribute_tag = DOUBLE;
    new_attribute->attribute_value.double_val = value;
    new_attribute->attribute_key = strndup(attr_name, MAX_ID_LEN);

    return new_attribute;
}


/* see item.h */
attribute_t* char_attr_new(char* attr_name, char value)
{
    attribute_t* new_attribute = malloc(sizeof(attribute_t));

    if (new_attribute == NULL) {
        fprintf(stderr, "Failed to allocate memory for new attribute");
        return NULL;
    }

    new_attribute->attribute_tag = CHARACTER;
    new_attribute->attribute_value.char_val = value;
    new_attribute->attribute_key = strndup(attr_name, MAX_ID_LEN);

    return new_attribute;
}


/* see item.h */
attribute_t* bool_attr_new(char* attr_name, bool value)
{
    attribute_t* new_attribute = malloc(sizeof(attribute_t));

    if (new_attribute == NULL) {
        fprintf(stderr, "Failed to allocate memory for new attribute");
        return NULL;
    }
    
    new_attribute->attribute_tag = BOOLE;
    new_attribute->attribute_value.bool_val = value;
    new_attribute->attribute_key = strndup(attr_name, MAX_ID_LEN);

    return new_attribute;
}


// TYPE-SPECIFIC SET_ATTR FUNCTIONS -------------------------------------------

/* see item.h */
int set_str_attr(item_t* item, char* attr_name, char* value)
{
    attribute_t* res = get_attribute(item, attr_name);
    if (res == NULL) {
        attribute_t* new_attribute = str_attr_new(attr_name, value);
        int rv = add_attribute_to_hash(item, new_attribute);
        return rv;
    } else if (res != NULL && res->attribute_tag != STRING) {
        return FAILURE; // skeleton for not overriding type
    } else {
        res->attribute_value.str_val = value;
        return SUCCESS;
    }
}


/* see item.h */
int set_int_attr(item_t* item, char* attr_name, int value)
{
    attribute_t* res = get_attribute(item, attr_name);
    if (res == NULL) {
        attribute_t* new_attribute = int_attr_new(attr_name, value);
        int rv = add_attribute_to_hash(item, new_attribute);
        return rv;
    } else if (res != NULL && res->attribute_tag != INTEGER) {
        return FAILURE; // skeleton for not overriding type
    } else {
        res->attribute_value.int_val = value;
        return SUCCESS;
    }
}


/* see item.h */
int set_double_attr(item_t* item, char* attr_name, double value)
{
    attribute_t* res = get_attribute(item, attr_name);
    if (res == NULL) {
        attribute_t* new_attribute = double_attr_new(attr_name, value);
        int rv = add_attribute_to_hash(item, new_attribute);
        return rv;
    } else if (res != NULL && res->attribute_tag != DOUBLE) {
        return FAILURE; // skeleton for not overriding type
    } else {
        res->attribute_value.double_val = value;
        return SUCCESS;
    }
}


/* see item.h */
int set_char_attr(item_t* item, char* attr_name, char value)
{
    attribute_t* res = get_attribute(item, attr_name);
    if (res == NULL) {
        attribute_t* new_attribute = char_attr_new(attr_name, value);
        int rv = add_attribute_to_hash(item, new_attribute);
        return rv;
    } else if (res != NULL && res->attribute_tag != CHARACTER) {
        return FAILURE; // skeleton for not overriding type
    } else {
        res->attribute_value.char_val = value;
        return SUCCESS;
    }
}


/* see item.h */
int set_bool_attr(item_t* item, char* attr_name, bool value)
{
    attribute_t* res = get_attribute(item, attr_name);
    if (res == NULL) {
        attribute_t* new_attribute = bool_attr_new(attr_name, value);
        int rv = add_attribute_to_hash(item, new_attribute);
        return rv;
    } else if (res != NULL && res->attribute_tag != BOOLE) {
        return FAILURE; // skeleton for not overriding type
    } else {
        res->attribute_value.bool_val = value;
        return SUCCESS;
    }
}


// TYPE-SPECIFIC GET_ATTR FUNCTIONS -------------------------------------------
/* see item.h */
char* get_str_attr(item_t *item, char* attr_name)
{
    attribute_t* res = get_attribute(item, attr_name);
    if (res == NULL)
    {
        return NULL;
    }
    if(res->attribute_tag != STRING)
    {
        return NULL; //attribute is not type string
    }
    return res->attribute_value.str_val;
}

/* see item.h */
int get_int_attr(item_t *item, char* attr_name)
{

    attribute_t* res = get_attribute(item, attr_name);
    if (res == NULL)
    {
        // value returned if search fails, open to alternative
        return -1;
    }
    if(res->attribute_tag != INTEGER)
    {
        return -1; //attribute is not type integer
    }
    return res->attribute_value.int_val;
}

/* see item.h */
double get_double_attr(item_t *item, char* attr_name)
{

    attribute_t* res = get_attribute(item, attr_name);
    if (res == NULL)
    {
        // value returned if search fails, open to alternative
        return -1.0;
    }
    if (res->attribute_tag != DOUBLE)
    {
        return -1.0; //attribute is not type double
    }
    return res->attribute_value.double_val;
}


/* see item.h */
char get_char_attr(item_t *item, char* attr_name)
{

    attribute_t* res = get_attribute(item, attr_name);
    if (res == NULL)
    {
        return '~';
    }
    if (res->attribute_tag != CHARACTER)
    {
        return '~'; //attribute is not type character
    }
    return res->attribute_value.char_val;
}

/* see item.h */
bool get_bool_attr(item_t *item, char* attr_name)
{
    attribute_t* res = get_attribute(item, attr_name);
    if (res == NULL)
    {
        return NULL;
    }
    if (res->attribute_tag != BOOLE)
    {
        return NULL; //attribute is not type boolean
    }
    return res->attribute_value.bool_val;
}


// ---------------------------------------------------------------------------

/* see item.h */
int attributes_equal(item_t* item_1, item_t* item_2, char* attribute_name)
{
    attribute_t* attribute_1 = get_attribute(item_1, attribute_name);
    attribute_t* attribute_2 = get_attribute(item_2, attribute_name);
    if(attribute_1==NULL || attribute_2==NULL)
    {
        return -1; //attribute does not exist for one or more items
    }
    if (attribute_1->attribute_tag != attribute_2->attribute_tag)
    {

        return -1; //could not compare attributes as they are of different types
    }
    int comparison = FAILURE;
    switch(attribute_1->attribute_tag)
    {
    case(DOUBLE):
        if (attribute_1->attribute_value.double_val ==
                attribute_2->attribute_value.double_val)
        {
            comparison = SUCCESS;
        }
        break;
    case(BOOLE):
        if (attribute_1->attribute_value.bool_val ==
                attribute_2->attribute_value.bool_val)
        {
            comparison = SUCCESS;
        }
        break;
    case(CHARACTER):
        if (attribute_1->attribute_value.char_val ==
                attribute_2->attribute_value.char_val)
        {
            comparison = SUCCESS;
        }
        break;
    case(STRING):
        if (!strcmp(attribute_1->attribute_value.str_val,
                    attribute_2->attribute_value.str_val))
        {
            comparison = SUCCESS;
        }
        break;
    case(INTEGER):
        if (attribute_1->attribute_value.int_val ==
                attribute_2->attribute_value.int_val)
        {
            comparison = SUCCESS;
        }
        break;
    }
    return comparison;
}




// FREEING AND DELETION FUNCTIONS ---------------------------------------------

/* see game_action.h */
int game_action_free(game_action_t* game_action)
{
    free(game_action->action_name);
    delete_condition_llist(game_action->conditions);
    delete_action_effect_llist(game_action->effects);
    free(game_action->success_str);
    free(game_action->fail_str);
    free(game_action);
    return SUCCESS;
}


/* see item.h */
int attribute_free(attribute_t *attribute)
{
    free(attribute->attribute_key);

    free(attribute);
    return SUCCESS;
}


/* see common-item.h */
int delete_all_attributes(attribute_hash_t* attributes)
{
    attribute_t *current_attribute, *tmp;
    HASH_ITER(hh, attributes, current_attribute, tmp)
    {
        /* deletes (attrs advances to next) */
        HASH_DEL(attributes, current_attribute);
        attribute_free(current_attribute);             /* free it */
    }
    return SUCCESS;
}

/* See item.h */
int item_free(item_t *item)
{
    free(item->item_id);
    free(item->short_desc);
    free(item->long_desc);
    delete_attribute_llist(item->class_multipliers);
    delete_all_attributes(item->attributes);
    // uthash_free(item->attributes, HASH_SIZE);
    if (item->stat_effects != NULL) {
        delete_all_stat_effects(item->stat_effects);
    }
    free(item);
    return SUCCESS;
}

/* See common.h*/
int delete_all_items(item_hash_t** items)
{
    if (items != NULL) HASH_CLEAR(hh, *items);

    return SUCCESS;
}

/* See item.h */
attribute_list_t *get_all_attributes(item_t *item)
{
    attribute_list_t *head = NULL;
    attribute_t *ITTMP_ATTR, *curr_attribute;
    attribute_list_t *tmp;
    HASH_ITER(hh, item->attributes, curr_attribute, ITTMP_ATTR)
    {
        tmp = malloc(sizeof(attribute_list_t));
        tmp->attribute = curr_attribute;
        LL_APPEND(head, tmp);
    }
    return head;
}

/* See item.h */
int delete_attribute_llist(attribute_list_t *head)
{
    attribute_list_t *elt, *tmp;
    LL_FOREACH_SAFE(head, elt, tmp)
    {
        LL_DELETE(head, elt);
	free(elt);
    }
    return SUCCESS;
}

/* See item.h */
attribute_list_t* create_list_attribute()
{
    attribute_list_t* rv = malloc(sizeof(attribute_list_t));
    if (rv == NULL)
    {
      return NULL; //Malloc failed
    }

    rv->attribute = NULL;
    rv->next = NULL;

    return rv; 
}
/*
 * Function that takes two attribute_list_ts and compares them.
 *
 * Parameters:
 * - attribute_list_t: points to node with one action
 * - attribute_list_t: points to node of another action
 *
 * Returns:
 * - int value that means 0: the same, 1: first string comes after second,
 *   -1: first string comes before second
 */
int attr_cmp(attribute_list_t *a1, attribute_list_t *a2)
{
  return strcmp(a1->attribute->attribute_key, a2->attribute->attribute_key);
}

/* See item.h */
bool list_contains_attribute(attribute_list_t *head, char* attr_name)
{
    if (attr_name == NULL || head->next == NULL)
    {
        return false;
    }
    attribute_list_t *tmp;
    attribute_list_t *like = calloc(1, sizeof(attribute_list_t));

    like->attribute = calloc(1, sizeof(attribute_t));
    like->attribute->attribute_key = attr_name;
    
    LL_SEARCH(head->next, tmp, like, attr_cmp);
    free(like->attribute);
    free(like);

    if (tmp)
        return true;
    else return false;
}

/* See item.h */
int add_attribute_to_list(attribute_list_t *head, attribute_t *attr)
{
    if (attr == NULL)
    {
        return FAILURE;
    }
    
    /* General Case where there could be n elements in the list */
    if (list_contains_attribute(head, attr->attribute_key))
        return SUCCESS;
    else
    {
        /* Create the to-be appended struct of new attribute */
        attribute_list_t *tmp = create_list_attribute(); 

        tmp->attribute = attr;
        tmp->next = NULL;

        LL_APPEND(head, tmp);
        return SUCCESS;
    }
}

/* See item.h */
int remove_attribute_from_list(attribute_list_t *head, char *attr_name)
{
    if (!list_contains_attribute(head, attr_name))
    {
        printf("\nNot Recognized\n");
        return FAILURE;
    }
    
    attribute_list_t *tmp;
    attribute_list_t *like = calloc(1, sizeof(attribute_list_t));

    like->attribute = calloc(1, sizeof(attribute_t));
    like->attribute->attribute_key = attr_name;

    LL_SEARCH(head->next, tmp, like, attr_cmp);
    free(like->attribute);
    free(like);

    if (tmp)
    {
        LL_DELETE(head->next, tmp);
        free(tmp);
        return SUCCESS;
    }
    else return FAILURE;

}

/* See item.h */
int delete_item_llist(item_list_t *head)
{
    item_list_t *elt, *tmp;
    LL_FOREACH_SAFE(head, elt, tmp)
    {
        LL_DELETE(head, elt);
        free(elt);
    }
    return SUCCESS;
}




// Functions to get attributes from a list ------------------------------------

/* see item.h */
attribute_t *list_get_attribute(attribute_list_t *head, char* attr_name)
{
    /* Return NULL on invalid inputs */
    if (attr_name == NULL || head == NULL || head->next == NULL)
    {
        return NULL;
    }

    attribute_list_t *like = calloc(1, sizeof(attribute_list_t));
    if (like == NULL) {
        fprintf(stderr, "calloc failed to allocate memory in list_get_attribute.");
        return NULL;
    }
    like->attribute = calloc(1, sizeof(attribute_t));
    if (like == NULL) {
        fprintf(stderr, "calloc failed to allocate memory in list_get_attribute.");
        return NULL;
    }
    like->attribute->attribute_key = attr_name;
    
    attribute_list_t *output;
    LL_SEARCH(head->next, output, like, attr_cmp);

    free(like->attribute);
    free(like);

    /* If no attribute is found, return NULL */
    if (output == NULL)
        return NULL;

    return output->attribute;
}

/* see item.h */
char* list_get_str_attr(attribute_list_t *head, char* attr_name)
{
    attribute_t* res = list_get_attribute(head, attr_name);
    if (res == NULL)
    {
        return NULL;
    }
    if(res->attribute_tag != STRING)
    {
        return NULL; //attribute is not type string
    }
    return res->attribute_value.str_val;
}

/* see item.h */
int list_get_int_attr(attribute_list_t *head, char* attr_name)
{

    attribute_t* res = list_get_attribute(head, attr_name);
    if (res == NULL)
    {
        // value returned if search fails, open to alternative
        return -1;
    }
    if(res->attribute_tag != INTEGER)
    {
        return -1; //attribute is not type integer
    }
    return res->attribute_value.int_val;
}

/* see item.h */
double list_get_double_attr(attribute_list_t *head, char* attr_name)
{
    attribute_t* res = list_get_attribute(head, attr_name);
    if (res == NULL)
    {
        // value returned if search fails, open to alternative
        return -1.0;
    }
    if (res->attribute_tag != DOUBLE)
    {
        return -1.0; //attribute is not type double
    }
    return res->attribute_value.double_val;
}

/* see item.h */
char list_get_char_attr(attribute_list_t *head, char* attr_name)
{

    attribute_t* res = list_get_attribute(head, attr_name);
    if (res == NULL)
    {
        return '~';
    }
    if (res->attribute_tag != CHARACTER)
    {
        return '~'; //attribute is not type character
    }
    return res->attribute_value.char_val;
}

/* see item.h */
bool list_get_bool_attr(attribute_list_t *head, char* attr_name)
{
    attribute_t* res = list_get_attribute(head, attr_name);
    if (res == NULL)
    {
        return NULL;
    }
    if (res->attribute_tag != BOOLE)
    {
        return NULL; //attribute is not type boolean
    }
    return res->attribute_value.bool_val;
}
