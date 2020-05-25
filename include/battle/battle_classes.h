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
    CLASS_BARD,
    CLASS_CLERIC,
    CLASS_PALADIN,
    CLASS_WIZARD
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
    STAT_SPEED,
    STAT_STRENGTH,
    STAT_DEXTERITY,
    STAT_CHARISMA
} possible_stats_t;


/* The mock  player class struct, which includes:
 * the enum class type
 * a short description of the class
 * which stat the class gets a bonus for
 * how much that bonus is
 */
typedef struct class
{
    class_type_t class_type;
    char *info;
    possible_stats_t stats;
    int bonus;
} class_t;


/*
 * Allocates a class
 *
 * Parameters:
 * - cl: a class type
 * - info: a short description of the class
 * - st: the stat that the class receives a bonus for
 * - bonus: the amount added to the designated stat
 *
 * Returns:
 * -A pointer to the class, or NULL if a class
 *  cannot be allocated
 */
class_t *new_class(class_type_t class_type, char* info,
		   possible_stats_t stats, double bonus);


/*
 * Initializes a class
 *
 * Parameters:
 * - class: A class. Must point to allocated memory.
 * - cl: a class type
 * - info: a short description of the class
 * - st: the stat that the class receives a bonus for
 * - bonus: the amount added to the designated stat
 *
 * Returns:
 * - 0 for success, 1 if an error occurs
 */
int init_class(class_t *class, class_type_t class_type, char* info,
	       possible_stats_t stats, double bonus);

/*
* Frees the resources associated with a class
* 
* Note: It will not free the substructs associated with the class.
*
* Parameters:
*  - class: A class pointer. Must point to a class allocated with new_class
*
* Returns:
*  - Always returns 0.
*/
int class_free(class_t *class);

#endif
