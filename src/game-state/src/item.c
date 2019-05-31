/* Implementations of the item struct */
#include "item.h"
#include <string.h>

// BASIC ITEM FUNCTIONS -------------------------------------------------------
/* see common-item.h*/
int item_init(item_t *new_item, char *item_id, char *short_desc,
    char *long_desc)
{
    assert(new_item != NULL);

    strcpy(new_item->item_id, item_id);
    strcpy(new_item->short_desc, short_desc);
    strcpy(new_item->long_desc, long_desc);

    return SUCCESS;
}

/* see item.h */
item_t *item_new(char *item_id, char *short_desc, char *long_desc)
{
    item_t *new_item = malloc(sizeof(item_t));
    new_item->item_id = malloc(MAX_ID_LEN * sizeof(char));
    new_item->short_desc = malloc(MAX_SDESC_LEN * sizeof(char));
    new_item->long_desc = malloc(MAX_LDESC_LEN * sizeof(char));

    int check = item_init(new_item, item_id, short_desc, long_desc);

    if (new_item == NULL || new_item->item_id == NULL ||
       new_item->short_desc == NULL || new_item->long_desc == NULL) {

       fprintf(stderr,
           "item_new(): item struct not properly malloced");
        return NULL;

    }

    if(check != SUCCESS) {
        return NULL;
    }

    return new_item;

}

int action_init(game_action_t *new_action, char *act_name,
    action_type_t *act_type)
{
    assert(new_action != NULL);

    strcpy(new_action->action_name, act_name);
    new_action->action_type = act_type;

    return SUCCESS;
}

/* see item.h */
game_action_t *game_action_new(char *act_name, action_type_t *act_type)
{
    game_action_t *new_action = malloc(sizeof(game_action_t));
    new_action->action_name = malloc(MAX_ID_LEN * sizeof(char));
    new_action->action_type = malloc(sizeof(action_type_t));

    int check = action_init(new_action, act_name, act_type);

    if (new_action == NULL || new_action->action_name == NULL ||
       new_action->action_type == NULL) {

        fprintf(stderr,
            "game_action_new(): game action struct not properly malloced");
        return NULL;

    }

    if(check != SUCCESS) {
        return NULL;
    }

    return new_action;

}

// ATTRIBUTE MANIPULATION FUNCTIONS -------------------------------------------
/* see common-item.h */
int add_attribute_to_hash(item_t* item, attribute_t* new_attribute) {
    attribute_t* check;
    HASH_FIND(hh, item->attributes, new_attribute->attribute_key,
        strlen(new_attribute->attribute_key), check);
    if (check != NULL) {
        fprintf(stderr, "Error: this attribute is already present.\n");
        return FAILURE;
    }
    HASH_ADD_KEYPTR(hh, item->attributes, new_attribute->attribute_key,
        strlen(new_attribute->attribute_key), new_attribute);
    return SUCCESS;
}

/* see common-item.h */
attribute_t *get_attribute(item_t *item, char* attr_name)
{
    attribute_t* return_value;
    HASH_FIND(hh, item->attributes, attr_name, strlen(attr_name), return_value);
    if (return_value == NULL) {
        return NULL;
    }
    return return_value;
}


/* see item.h */
int set_str_attr(item_t* item, char* attr_name, char* value)
{
    attribute_t* res = get_attribute(item, attr_name);
    if (res == NULL)
    {
        attribute_t* new_attribute = malloc(sizeof(attribute_t));
        new_attribute->attribute_tag = STRING;
        new_attribute->attribute_value.str_val = value;
	new_attribute->attribute_key = strndup(attr_name, 100);
        int rv = add_attribute_to_hash(item, new_attribute);
        return rv;
    }
    else if (res != NULL && res->attribute_tag != STRING) {
        return FAILURE; // skeleton for not overriding type
    }
    else
    {
        res->attribute_value.str_val = value;
        return SUCCESS;
    }
}

// TYPE-SPECIFIC SET_ATTR FUNCTIONS -------------------------------------------
/* see item.h */
int set_int_attr(item_t* item, char* attr_name, int value)
{
    attribute_t* res = get_attribute(item, attr_name);
    if (res == NULL)
    {
        attribute_t* new_attribute = malloc(sizeof(attribute_t));
        new_attribute->attribute_tag = INTEGER;
        new_attribute->attribute_value.int_val = value;
	new_attribute->attribute_key = strndup(attr_name, 100);
        int rv = add_attribute_to_hash(item, new_attribute);
        return rv;
    }
    else if (res != NULL && res->attribute_tag != INTEGER) {
        return FAILURE; // skeleton for not overriding type
    }
    else
    {
        res->attribute_value.int_val = value;
        return SUCCESS;
    }
}

/* see item.h */
int set_double_attr(item_t* item, char* attr_name, double value)
{
    attribute_t* res = get_attribute(item, attr_name);
    if (res == NULL)
    {
        attribute_t* new_attribute = malloc(sizeof(attribute_t));
        new_attribute->attribute_tag = DOUBLE;
        new_attribute->attribute_value.double_val = value;
        new_attribute->attribute_key = strndup(attr_name, 100);
        int rv = add_attribute_to_hash(item, new_attribute);
        return rv;
    }
    else if (res != NULL && res->attribute_tag != DOUBLE) {
        return FAILURE; // skeleton for not overriding type
    }
    else
    {
        res->attribute_value.double_val = value;
        return SUCCESS;
    }

}

/* see item.h */
int set_char_attr(item_t* item, char* attr_name, char value)
{
    attribute_t* res = get_attribute(item, attr_name);
    if (res == NULL)
    {
        attribute_t* new_attribute = malloc(sizeof(attribute_t));
        new_attribute->attribute_tag = CHARACTER;
        new_attribute->attribute_value.char_val = value;
	new_attribute->attribute_key = strndup(attr_name, 100);
        int rv = add_attribute_to_hash(item, new_attribute);
        return rv;
    }
    else if (res != NULL && res->attribute_tag != CHARACTER) {
        return FAILURE; // skeleton for not overriding type
    }

    else
    {
        res->attribute_value.char_val = value;
        return SUCCESS;
    }
}

/* see item.h */
int set_bool_attr(item_t* item, char* attr_name, bool value)
{
    attribute_t* res = get_attribute(item, attr_name);
    if (res == NULL)
    {
        attribute_t* new_attribute = malloc(sizeof(attribute_t));
        new_attribute->attribute_tag = BOOLE;
        new_attribute->attribute_value.bool_val = value;
	new_attribute->attribute_key = strndup(attr_name, 100);
        int rv = add_attribute_to_hash(item, new_attribute);
        return rv;
    }
    else if (res != NULL && res->attribute_tag != BOOLE) {
        return FAILURE; // skeleton for not overriding type
    }

    else
    {
        res->attribute_value.bool_val = value;
        return SUCCESS;
    }
}

int set_act_attr(item_t* item, char* attr_name, action_type_t *value)
{
    attribute_t* res = get_attribute(item, attr_name);
    if (res == NULL)
    {
        attribute_t* new_attribute = malloc(sizeof(attribute_t));
        new_attribute->attribute_tag = ACTION;
        new_attribute->attribute_value.act_val = game_action_new(attr_name,
            value);
	new_attribute->attribute_key = strndup(attr_name, 100);
        int rv = add_attribute_to_hash(item, new_attribute);
        return rv;
    }
    else if (res != NULL && res->attribute_tag != ACTION) {
        return FAILURE; // skeleton for not overriding type
    }

    else
    {
        // this needs to be discussed
        res->attribute_value.act_val = game_action_new(attr_name, value);
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
        fprintf(stderr, "Error: attribute get failed.\n");
        return NULL;
    }
    if(res->attribute_tag != STRING)
    {
        fprintf(stderr, "Error: attribute is not type string.\n");
        return NULL;
    }
    return res->attribute_value.str_val;
}

/* see item.h */
int get_int_attr(item_t *item, char* attr_name) {

    attribute_t* res = get_attribute(item, attr_name);
    if (res == NULL)
    {
        fprintf(stderr, "Error: attribute get failed.\n");
        // value returned if search fails, open to alternative
        return -1;
    }
    if(res->attribute_tag != INTEGER)
    {
        fprintf(stderr, "Error: attribute is not type integer.\n");
        return -1;
    }
    return res->attribute_value.int_val;
}

/* see item.h */
double get_double_attr(item_t *item, char* attr_name) {

  attribute_t* res = get_attribute(item, attr_name);
    if (res == NULL)
    {
        fprintf(stderr, "Error: attribute does not exist.\n");
        // value returned if search fails, open to alternative
        return -1.0;
    }
    if (res->attribute_tag != DOUBLE)
    {
        fprintf(stderr, "Error: attribute is not type double.\n");
        return -1.0;
    }
    return res->attribute_value.double_val;
}


/* see item.h */
char get_char_attr(item_t *item, char* attr_name) {

    attribute_t* res = get_attribute(item, attr_name);
    if (res == NULL)
    {
        fprintf(stderr, "Error: attribute get failed.\n");
        return '~';
    }
    if (res->attribute_tag != CHARACTER)
    {
        fprintf(stderr, "Error: attribute is not type character.\n");
        return '~';
    }
    return res->attribute_value.char_val;
}

/* see item.h */
bool get_bool_attr(item_t *item, char* attr_name) {
    attribute_t* res = get_attribute(item, attr_name);
    if (res == NULL)
    {
        fprintf(stderr, "Error: attribute get failed.\n");
        return NULL;
    }
    if (res->attribute_tag != BOOLE)
    {
        fprintf(stderr, "Error: attribute is not type boolean.\n");
        return NULL;
    }
    return res->attribute_value.bool_val;
}

game_action_t *get_act_attr(item_t *item, char* attr_name) {
    attribute_t* res = get_attribute(item, attr_name);

    if (res == NULL)
    {
        fprintf(stderr, "Error: attribute get failed.\n");
        return NULL;
    }
    if (res->attribute_tag != ACTION)
    {
        fprintf(stderr, "Error: attribute is not type boolean.\n");
        return NULL;
    }
    return res->attribute_value.act_val;
}

 // ---------------------------------------------------------------------------

/* see item.h */
int attributes_equal(item_t* item_1, item_t* item_2, char* attribute_name)
{
    attribute_t* attribute_1 = get_attribute(item_1, attribute_name);
    attribute_t* attribute_2 = get_attribute(item_2, attribute_name);
    if(attribute_1==NULL || attribute_2==NULL)
    {
        fprintf(stderr,
            "Error: attribute does not exist for one or more items\n");
        return -1;
    }
    if (attribute_1->attribute_tag != attribute_2->attribute_tag)
    {
        fprintf(stderr,
            "Error: could not compare attributes as they are of different types\n");
        return -1;
    }
    int comparison = 0;
    switch(attribute_1->attribute_tag)
    {
        case(DOUBLE):
            if (attribute_1->attribute_value.double_val ==
                attribute_2->attribute_value.double_val)
            {
                comparison = 1;
            }
            break;
        case(BOOLE):
            if (attribute_1->attribute_value.bool_val ==
                attribute_2->attribute_value.bool_val)
            {
                comparison = 1;
            }
            break;
        case(CHARACTER):
            if (attribute_1->attribute_value.char_val ==
                attribute_2->attribute_value.char_val)
            {
                comparison = 1;
            }
            break;
        case(STRING):
            if (!strcmp(attribute_1->attribute_value.str_val,
                attribute_2->attribute_value.str_val))
            {
                comparison = 1;
            }
            break;
        case(INTEGER):
            if (attribute_1->attribute_value.int_val ==
                attribute_2->attribute_value.int_val)
            {
                comparison = 1;
            }
            break;
        case(ACTION):
        // just for now to get prototype out, we need an actions_eq function
            comparison = 1;
            break;
    }
    return comparison;
}

/* see item.h */
int add_allowed_action(item_t* item, char *act_name, action_type_t *act_type)
{
    int rv = set_act_attr(item, act_name, act_type);
    return rv;
}

/* see item.h */
int allowed_action(item_t* item, char* action_name)
{
    attribute_t* action = get_attribute(item, action_name);
    if (action == NULL)
    {
        return FAILURE;
    }
    else
    {
        return SUCCESS;
    }
}

// FREEING AND DELETION FUNCTIONS ---------------------------------------------

int game_action_free(game_action_t *action_tofree) {
    free(action_tofree->action_name);
    free(action_tofree->action_type);
    free(action_tofree);

    return SUCCESS;
}


/* see item.h */
int attribute_free(attribute_t *attribute) {
    free(attribute->attribute_key);

    if (attribute->attribute_tag == ACTION) {
        game_action_free(attribute->attribute_value.act_val);
        free(attribute);
        return SUCCESS;
    }


    free(attribute);
    return SUCCESS;
}


/* see common-item.h */
int delete_all_attributes(attribute_hash_t attributes)
{
    attribute_t *current_attribute, *tmp;
    HASH_ITER(hh, attributes, current_attribute, tmp) {
        /* deletes (attrs advances to next) */
        HASH_DEL(attributes, current_attribute);
        attribute_free(current_attribute);             /* free it */
    }
    return SUCCESS;
}

/* See item.h */
int item_free(item_t *item) {
    free(item->item_id);
    free(item->short_desc);
    free(item->long_desc);
    delete_all_attributes(item->attributes);
    // uthash_free(item->attributes, HASH_SIZE);
    free(item);
    return SUCCESS;
}

/* See common.h*/
int delete_all_items(item_hash_t items) {
    item_t *current_item, *tmp;
    HASH_ITER(hh, items, current_item, tmp) {
        HASH_DEL(items, current_item);  /* deletes (items advances to next) */
        item_free(current_item);             /* free it */
    }
    return SUCCESS;
}
