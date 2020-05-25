#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "battle/battle_classes.h"


/* See battle_classes.h */
int init_class(class_t *class, class_type_t cl, char* info, possible_stats_t st, double bonus)
{
    assert(class != NULL);
    assert(info != NULL);

    class->cl = cl;

    class->info = (char*) calloc(MAX_CLASS_INFO_LEN + 1, sizeof(char));
    strncpy(class->info, info, MAX_CLASS_INFO_LEN + 1);

    class->st = st;

    class->bonus = bonus;

    return 0;
}


/* See battle_classes.h */
class_t *new_class(class_type_t cl, char* info, possible_stats_t st, double bonus)
{
    class_t *class = (class_t*) calloc(1, sizeof(class_t));
    int rc;

    if(class == NULL)
    {
        fprintf(stderr,"Could not allocate memory\n");
        return NULL;
    }

    rc = init_class(class, cl, info, st, bonus);

    if(rc != 0)
    {
        fprintf(stderr,"Could not initialize class\n");
        return NULL;
    }

    return class;
}

/* Creates test bard class
 *
 * Parameters:
 *  none, values are hard coded in
 *
 * Returns:
 *  - A pointer to a test class
 *
 */
class_t *make_test_bard()
{
    char* bard_des = "Charismatic, always has a joke, song, or moving speech ready";
    class_t *test_bard = new_class(BARD, bard_des, CHRSMA, 2.0);
    return test_bard;
}


/* Creates test cleric class
 *
 * Parameters:
 *  none, values are hard coded in
 *
 * Returns:
 *  - A pointer to a test class
 *
 */
class_t *make_test_cleric()
{
    char* cleric_des = "Fueled by divine inspiration, devout to the craft";
    class_t *test_cleric = new_class(CLERIC, cleric_des, STR, 2.0);
    return test_cleric;
}


/* Creates test paladin class
 *
 * Parameters:
 *  none, values are hard coded in
 *
 * Returns:
 *  - A pointer to a test class
 *
 */
class_t *make_test_paladin()
{
    char* paladin_des = "Driven and committed to justice";
    class_t *test_paladin = new_class(PALADIN, paladin_des, DEX, 2.0);
    return test_paladin;
}


/* Creates test wizard  class
 *
 * Parameters:
 *  none, values are hard coded in
 *
 * Returns:
 *  - A pointer to a test class
 *
 */
class_t *make_test_wizard()
{
    char* wizard_des = "Draws power from nature";
    class_t *test_wizard = new_class(WIZARD, wizard_des, SPD, 2.0);
    return test_wizard;
}


