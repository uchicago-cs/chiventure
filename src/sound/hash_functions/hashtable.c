
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include "uthash.h"

typedef struct{
    // path to sound file
    char* path;
    // duration of sound
    double duration;
    // name of sound
    char* name;
    // id for finding it in hash table
    int id; 
    // makes struct hashable
    UT_hash_handle hh; 
} sound_t;


struct sound_t *users = NULL;


void add_user(int user_id, char *name) {
    struct sound_t *s;

    HASH_FIND_INT(users, &user_id, s);  /* id already in the hash? */
    if (s == NULL) {
      s = (struct sound_t *)malloc(sizeof *s);
      s->id = user_id;
      HASH_ADD_INT(users, id, s);  /* id: name of key field */
    } else {
        printf("ID already in hashtable, sound not added");
    }
    strcpy(s->name, name);
}


struct sound_t *find_user(int user_id) {
    struct sound_t *s;

    HASH_FIND_INT(users, &user_id, s);
    return s;
}


sound_t s;
s->id = 1;
s->duration = 5;
add_user(s->id, first);
sound_t* rv = find_user(s->id);
printf(rv->id);
printf(rv->duration);


