#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "libobj/obj.h"
#include "game-state/player.h"
#include "common/utlist.h"

typedef struct class{
    obj_t* info;
    // to be replaced with the stats_t object
    obj_t* stats;
    struct class *next;
} class_t;

class_t* class_new(obj_t *info, obj_t *stats){
    class_t* class = (class_t*) malloc(sizeof(class_t));
    
    assert(class != NULL);

    class->info = info;
    class->stats = stats;

    return class;
}

int free_class(class_t* class){
    obj_free_all(class->info);
    obj_free_all(class->stats);
    free(class);
    return 0;
}

int show_all_class(class_t* list){
    if(list != NULL){
        printf("Class: %s\n", list->info->id);
        printf("    %s\n", obj_get_str(list->info, "shortdesc"));
        show_all_class(list->next);
    }
    return 0;
}

int show_class_info(class_t* class){
    assert(class != NULL);
    printf("Class: %s\n", class->info->id);
    printf("    %s\n", obj_get_str(class->info, "longdesc"));
    return 0;
}

int select_class(player_t* player, class_t* class){
    /* I can't modify the player struct as of now, so lets say
     * this function modifies the player or game struct to set
     * the player's class. */
    assert(class != NULL);
    printf("Class set as %s\n", class->info->id);
    return 0;
}

int main()
{
    // Warrior Class
    obj_t* warclass;
    obj_t* warstat;

    warclass = obj_new("Warrior");
    obj_set_str(warclass, "shortdesc", "Mechanically, the warrior focuses on \
up-close physical damage with weapons and survives enemy attacks \
using heavy armor.\n");
    obj_set_str(warclass, "longdesc", "The warrior is the ultimate armor and \
weapons expert, relying on physical strength and years of training to \
deal with any obstacle. Mechanically, the warrior \
focuses on up-close physical damage with weapons and survives enemy \
attacks using heavy armor.\n");
    warstat = obj_new("Warrior stats");
    obj_set_int(warstat, "HP", 25);
    obj_set_int(warstat, "XP", 0);
    obj_set_int(warstat, "speed", 10);
    obj_set_int(warstat, "pdef", 15);
    obj_set_int(warstat, "patk", 25);
    obj_set_int(warstat, "ratk", 5);
    obj_set_int(warstat, "mdef", 5);
    obj_set_int(warstat, "matk", 5);
    obj_set_int(warstat, "MP", 15);

    class_t* warrior;
    warrior = class_new(warclass, warstat);

    // Monk Class
    obj_t* monkclass;
    obj_t* monkstat;

    monkclass = obj_new("Monk");
    obj_set_str(monkclass, "shortdesc", "A monk's true skill lies in dexterity \
and athletic training.\n");
    obj_set_str(monkclass, "longdesc", "The monk is a martial arts master, \
experienced in direct hand-to-hand combat. Some monks may fight with a \
weapon, and others may learn to manipulate magic within the body, but a \
monk's true skill lies in dexterity and athletic training.\n");
    monkstat = obj_new("Monk stats");
    obj_set_int(monkstat, "HP", 22);
    obj_set_int(monkstat, "XP", 0);
    obj_set_int(monkstat, "speed", 14);
    obj_set_int(monkstat, "pdef", 14);
    obj_set_int(monkstat, "patk", 20);
    obj_set_int(monkstat, "ratk", 8);
    obj_set_int(monkstat, "mdef", 25);
    obj_set_int(monkstat, "matk", 5);
    obj_set_int(monkstat, "MP", 20);

    class_t* monk;
    monk = class_new(monkclass, monkstat);

    // Sorcerer Class
    obj_t* sorclass;
    obj_t* sorstat;

    sorclass = obj_new("Sorcerer");
    obj_set_str(sorclass, "shortdesc", "The sorcerer is a pure spellcaster, \
useless at most physical tasks but extremely good at using magic.\n");
    obj_set_str(sorclass, "longdesc", "Sorcerers spend their lives studying \
ancient magical tomes, arming themselves with spells and magical abilities \
for every situation. The sorcerer is a pure spellcaster, useless at most \
physical tasks but extremely good at using, detecting, and redirecting \
magic both in and out of combat.\n");
    sorstat = obj_new("Monk stats");
    obj_set_int(sorstat, "HP", 22);
    obj_set_int(sorstat, "XP", 0);
    obj_set_int(sorstat, "speed", 14);
    obj_set_int(sorstat, "pdef", 14);
    obj_set_int(sorstat, "patk", 20);
    obj_set_int(sorstat, "ratk", 8);
    obj_set_int(sorstat, "mdef", 25);
    obj_set_int(sorstat, "matk", 5);
    obj_set_int(sorstat, "MP", 20);

    class_t* sorcerer;
    sorcerer = class_new(sorclass, sorstat);
    player_t* player;

    // Setting up the list of classes loaded by Chiventure
    class_t* classlist = warrior;
    LL_PREPEND(classlist, monk);
    LL_PREPEND(classlist, sorcerer);

    // Starting the class selection
    show_all_class(classlist);
    printf("\n");
    printf("Showing detailed information of %s class.\n", sorcerer->info->id);
    show_class_info(sorcerer);
    printf("Are you sure you want to choose %s for your class?\n", sorcerer->info->id);
    select_class(player, sorcerer);

    free_class(sorcerer);
    free_class(warrior);
    free_class(monk);
}