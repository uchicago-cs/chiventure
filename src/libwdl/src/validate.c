#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "validate.h"


/* see validate.h */
bool list_type_check(attr_list_t *ls, bool(*validate)(obj_t*))
{
    if (ls == NULL)
        return false; // if the function returns false, it will halt parsing

    bool result = true;
    attr_list_t *curr = ls;

    while(curr != NULL) {
        result = (result && (*validate)(curr->obj));
        curr = curr->next;
    }

    return result;
}


/* see validate.h */
bool list_print(attr_list_t *ls, bool(*print)(obj_t*))
{
    if (ls == NULL)
        return;

    attr_list_t *curr = ls;

    while(curr != NULL) {
        (*print)(curr->obj);
        curr = curr->next;
    }
}


// THIS IS TEMPORALLY COMMENTED OUT TO PREVENT COMPILATION ERRORS //
/* See validate.h
void print_room(obj_t *obj, char *str)
{
    // Initialize strings for fields within object struct
    char *id = ".id";
    char *short_desc = ".short_desc";
    char *long_desc = ".long_desc";

    // Allocate memory for new strings and copy in str
    char *id_str = (char*) malloc(sizeof(char)*30);
    strcpy(id_str, str);
    char *short_str = (char*) malloc(sizeof(char)*30);
    strcpy(short_str, str);
    char *long_str = (char*) malloc(sizeof(char)*30);
    strcpy(long_str, str);

    // Concatenate str with field strings
    strcat(id_str, id);
    strcat(short_str, short_desc);
    strcat(long_str, long_desc);

    // Print id, short_desc, and long_desc
    printf("%s: %c\n", id_str, obj_get_char(obj, id_str));
    printf("%s: %s\n", short_str, obj_get_str(obj, short_str));
    printf("%s: %s\n", long_str, obj_get_str(obj, long_str));

    // Free strings
    free(id_str);
    free(short_str);
    free(long_str);
}


/* See validate.h
void print_item(obj_t *obj, char *str)
{
    // Initialize strings for fields within object struct
    char *id = ".id";
    char *short_desc = ".short_desc";
    char *long_desc = ".long_desc";

    // Allocate memory for new strings and copy in str
    char *id_str = (char*) malloc(sizeof(char)*30);
    strcpy(id_str, str);
    char *short_str = (char*) malloc(sizeof(char)*30);
    strcpy(short_str, str);
    char *long_str = (char*) malloc(sizeof(char)*30);
    strcpy(long_str, str);

    // Concatenate str with field strings
    strcat(id_str, id);
    strcat(short_str, short_desc);
    strcat(long_str, long_desc);

    // Print id, short_desc, and long_desc
    printf("%s: %s\n", id_str, obj_get_str(obj, id_str));
    printf("%s: %s\n", short_str, obj_get_str(obj, short_str));
    printf("%s: %s\n", long_str, obj_get_str(obj, long_str));

    // Free strings
    free(id_str);
    free(short_str);
    free(long_str);
}


/* See validate.h
void print_game(obj_t *obj, char *str1, char *str2)
{
    // Initialize strings for fields within object struct
    char *start = ".start";
    char *intro = ".intro";

    // Allocate memory for new strings and copy in str
    char *start_str = (char*) malloc(sizeof(char)*30);
    strcpy(start_str, str1);
    char *intro_str = (char*) malloc(sizeof(char)*30);
    strcpy(intro_str, str2);

    // Concatenate str with field strings
    strcat(start_str, start);
    strcat(intro_str, intro);

    // Print id, short_desc, and long_desc
    printf("%s: %c\n", start_str, obj_get_char(obj, start_str));
    printf("%s: %s\n", intro_str, obj_get_str(obj, intro_str));

    // Free strings
    free(start_str);
    free(intro_str);
}
*/

/* See validate.h */
bool verify_item(obj_t *obj, char *str)
{
    // Initialize strings for fields within object struct
    char *id = ".id";
    char *short_desc = ".short_desc";
    char *long_desc = ".long_desc";

    // Allocate memory for new strings and copy in str
    char *id_str = malloc(sizeof(char) * 30);
    strcpy(id_str, str);
    char *short_str = malloc(sizeof(char) * 30);
    strcpy(short_str, str);
    char *long_str = malloc(sizeof(char) * 30);
    strcpy(long_str, str);

    // Concatenate str with field strings
    strcat(id_str, id);
    strcat(short_str, short_desc);
    strcat(long_str, long_desc);

    // verify types of fields
    bool id_ver = true, short_ver = true, long_ver = true;
    if (obj_get_type(obj, id_str) != TYPE_STR && obj_get_type(obj, id_str) != TYPE_CHAR)
        id_ver = false;
    if (obj_get_type(obj, short_str) != TYPE_STR)
        short_ver = false;
    if (obj_get_type(obj, long_str) != TYPE_STR)
        long_ver = false;

    // Free strings
    free(id_str);
    free(short_str);
    free(long_str);

    return (id_ver && short_ver && long_ver);
}


/* connections_get_list()
 * a helper function for check_connections that gets a list of connections
 * associated with a room object
 *
 * parameters:
 *  - obj: a room object
 *
 * returns:
 *  - an attribute list of all the connections
 *  - null if an error occurs or no list can be generated
 */
attr_list_t *connections_get_list(obj_t *obj)
{
    obj_t *connections = obj_get_attr(obj, "connections", false);

    if (connections == NULL)
        return NULL;
    else
        return obj_list_attr(connections);
}

/* check_connection_attr()
 * a helper function for check_connections() that checks the attributes of connections
 * associated with a room object
 *
 * parameters:
 * - obj: a connection object
 *
 * returns:
 * - true if connection types match, else return false
 */
bool check_connection_attr(obj_t *obj)
{
    // verify types of fields
    bool id = true, direction = true, through = true;

    if (obj_get_type(obj, "to") != TYPE_STR && obj_get_type(obj, "to") != TYPE_CHAR)
        id = false;
    if (obj_get_type(obj, "direction") != TYPE_STR)
        direction = false;
    if (obj_get_type(obj, "through") != TYPE_STR)
        through = false;

    return (id && direction && through);
}

/* connection_type_check()
 * a helper function for room_type_check that checks all connections and its
 * attributes associated with a room object
 *
 * parameters:
 * - obj: a room object
 *
 * returns:
 * - true if attributes of all connections match, else return false
 */
bool connection_type_check(obj_t *obj)
{
    attr_list_t *ls = connections_get_list(obj);
    
    // call connection_type_check on each connection
    bool check = list_type_check(ls, check_connection_attr);

    return check;
}

/* See validate.h */
bool room_type_check(obj_t *obj)
{
    // verify types of fields
    bool id_ver = true, short_ver = true, long_ver = true;

    if (obj_get_type(obj, "id") != TYPE_STR && obj_get_type(obj, "id") != TYPE_CHAR)
        id_ver = false;
    if (obj_get_type(obj, "short_desc") != TYPE_STR)
        short_ver = false;
    // Revise
    if (obj_get_type(obj, "long_desc") != TYPE_STR)
        long_ver = false;
    // verify connections
    bool connections_ver = connection_type_check(obj);

    return (id_ver && short_ver && long_ver && connections_ver);
}


/* See validate.h */
bool verify_game(obj_t *obj, char *str1, char *str2)
{
    // Initialize strings for fields within object struct
    char *start = ".start";
    char *intro = ".intro";

    // Allocate memory for new strings and copy in str
    char *start_str = malloc(sizeof(char) * 30);
    strcpy(start_str, str1);
    char *intro_str = malloc(sizeof(char) * 30);
    strcpy(intro_str, str2);

    // Concatenate str with field strings
    strcat(start_str, start);
    strcat(intro_str, intro);

    // verify types of fields
    bool start_ver = true, intro_ver = true;
    if (obj_get_type(obj, start_str) != TYPE_CHAR)
        start_ver = false;
    if (obj_get_type(obj, intro_str) != TYPE_STR)
        intro_ver = false;

    // Free strings
    free(start_str);
    free(intro_str);

    return (start_ver && intro_ver);
}
