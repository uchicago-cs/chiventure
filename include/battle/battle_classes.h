#ifndef BATTLE_CLASSES_H
#define BATTLE_CLASSES_H

#include <stdbool.h>
#include <string.h>


/* A mock player class type enum that 
 * includes 4 classes:
 * bard
 * cleric 
 * paladin 
 * wizard 
 */
typedef enum class_type
{
    bard,
    cleric,
    paladin,
    wizard
} class_type_t;


/* Players get stat bonuses based on their class.
 * This enum type is part of the class struct. Whichever stat
 * is stored in class_t.st is increased by class_t.bonus
 * includes the following mock stats:
 * speed (spd)
 * strength (str)
 * dexterity (dex)
 * charisma (chrsma) 
 */
typedef enum possible_stats
{
    spd,
    str,
    dex,
    chrsma
} possible_stats_t;


/* The mock  player class struct, which includes:
 * the enum class type 
 * a short description of the class
 * which stat the class gets a bonus for
 * how much that bonus is
 */
typedef struct class
{
    class_type_t cl;
    char *info;
    possible_stats_t st;
    int bonus;
} class_t;


#endif
