#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse.h"

/* See parse.h */
void print_room_item(obj_t *obj, char *str)
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
    strcpy(long_str, str)

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
void print_game(obj_t *obj, char *str)
{
    // Initialize strings for fields within object struct
    char *start = ".start";
    char *intro = ".intro";

    // Allocate memory for new strings and copy in str
    char *start_str = (char*) malloc(sizeof(char)*30);
    strcpy(start_str, str);
    char *intro_str = (char*) malloc(sizeof(char)*30);
    strcpy(intro_str, str);

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
