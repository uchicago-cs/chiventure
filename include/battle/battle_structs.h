#ifndef BATTLE_STRUCTS_H
#define BATTLE_STRUCTS_H

#include <stdbool.h>
#include <string.h>

/* max name length */
#define MAX_NAME_LEN (50)

/* stats stub */
typedef struct stat {
    int speed;
    int strength;
    int dexterity;
    int hp;
    int max_hp;
    int xp;
} stat_t;


#endif
