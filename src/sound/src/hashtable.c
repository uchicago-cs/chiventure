#include "sound/sound.h"

/* This code is to test functionality of hash functions in order to 
    create a hash table to store sound structs. 
    Source: https://troydhanson.github.io/uthash/userguide.html*/



/* Declares a hash as a NULL-initalized pointer */ 

sound_t *users = NULL;


/* Adds an item to a hash */

void add_user(int user_id, char *name) {
    sound_t *s;
    s = (sound_t*)malloc(sizeof(sound_t));
    s->id = user_id;
    strcpy(s->name, name);
    HASH_ADD_INT(users, id, s);  /* id: name of key field */
}

/*Finds a structure in the hash based on an int key */

sound_t *find_user(int user_id) {
    sound_t *s;

    HASH_FIND_INT(users, &user_id, s);
    return s;
}




