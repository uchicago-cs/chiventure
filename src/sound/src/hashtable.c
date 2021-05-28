#include "sound/sound.h"

sound_t *users = NULL;


void add_user(int user_id, char *name) {
    sound_t *s;
    s = (sound_t*)malloc(sizeof(sound_t));
    s->id = user_id;
    strcpy(s->name, name);
    HASH_ADD_INT(users, id, s);  /* id: name of key field */
}



sound_t *find_user(int user_id) {
    sound_t *s;

    HASH_FIND_INT(users, &user_id, s);
    return s;
}

int main(){
    sound_t* sound;
    sound->id = 1;
    sound->wavLength = 5;
    add_user(sound->id, "first");
    sound_t* rv = find_user(sound->id);
    printf("%d", rv->id);
    printf("%f", rv->wavLength);
}




