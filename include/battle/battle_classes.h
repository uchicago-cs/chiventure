#ifndef BATTLE_CLASSES_H
#define BATTLE_CLASSES_H

/** The player class struct, which includes the enum class, a short
description of the class, which stat the class gets a bonus for, and
how much that bonus is **/
typedef struct class
{
    class_type_t cl;
    char *info;
    possible_stats_t st;
    int bonus;
} class_t;


/* class stub */
typedef enum class_type
{
    bard,
    cleric,
    paladin,
    wizard
} class_type_t;


/** Players get stat bonuses based on their class.
This enum type is part of the class struct. Whichever stat
is stored in class_t.st is increased by class_t.bonus **/
typedef enum possible_stats
{
    spd,
    str,
    dex,
    chrsma
} possible_stats_t;

#endif
