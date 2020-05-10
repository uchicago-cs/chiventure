#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../../../include/libobj/obj.h"
#include "../../../include/game-state/player.h"

typedef struct{
    obj_t class;
} class_t;

typedef struct{
    class_t* class;
    class_list* next;
} class_list;

class_t* class_new(obj_t obj){
    class_t* class = (class_t*) malloc(sizeof(class_t));
    
    assert(class != NULL);

    class->class = obj;

    return class;
}

int free_class(class_t* class){
    obj_free_all(class);
    return 0;
}

class_list* class_cons(class_t* class, class_list* list){
    class_list* classlist = (class_list*) malloc(sizeof(class_list));

    assert(classlist != NULL);

    classlist->class = class;
    classlist->next = list;

    return classlist;
}

int free_class_list(class_list* list){
    assert(list != NULL);
    if(list->next == NULL){
        free(list);
    } else {
        free_class_list(list->next);
        free(list);
    }
    return 0;
}

int show_all_class(class_list* list){
    //TODO
    return 0;
}

int show_class_info(class_t* class){
    //TODO
    return 0;
}

int select_class(player_t* player, class_t* class){
    /* I can't modify the player struct as of now, so lets say
     * this function modifies the player or game struct to set
     * the player's class. */
    assert(class != NULL);
    printf("Class set as %s\n", class->class.id);
    return 0;
}

int main(int argc, char *argv[])
{
    obj_t* setclasswar;

    setclasswar = obj_new("Warrior");
    obj_set_str(setclasswar, "shortdesc", "Mechanically, the warrior focuses on \
    up-close physical damage with weapons and survives enemy attacks \
    using heavy armor.\n");
    obj_set_str(setclasswar, "longdesc", "The warrior is the ultimate armor and \
    weapons expert, relying on physical strength and years of training to \
    deal with any obstacle. Mechanically, the warrior \
    focuses on up-close physical damage with weapons and survives enemy \
    attacks using heavy armor.\n");
    obj_set_str(setclasswar, "stats", "Warrior stats\n");

    class_t* warrior;
    warrior->class = *setclasswar;

    //Add more classes, functions, etc. 

    obj_free_all(setclasswar);
}