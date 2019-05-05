#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse.h"

/* See parse.h */
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


/* See parse.h */
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


/* See parse.h */
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


/* See parse.h */
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


/* See parse.h */
bool verify_room(obj_t *obj, char *str)
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


/* See parse.h */
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