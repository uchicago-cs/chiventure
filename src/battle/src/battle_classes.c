#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "battle/battle_classes.h"


/* See battle_classes.h */
int init_class(class_t *class, class_type_t class_type, char* info,
               possible_stats_t stats, double bonus)
{
    assert(class != NULL);
    assert(info != NULL);

    class->class_type = class_type;

    class->info = (char*) calloc(MAX_CLASS_INFO_LEN, sizeof(char));
    strncpy(class->info, info, MAX_CLASS_INFO_LEN);

    class->stats = stats;

    class->bonus = bonus;

    return 0;
}


/* See battle_classes.h */
class_t *new_class(class_type_t class_type, char* info,
                   possible_stats_t stats, double bonus)
{
    class_t *class = (class_t*) calloc(1, sizeof(class_t));
    int rc;

    if(class == NULL)
    {
        fprintf(stderr,"Could not allocate memory\n");
        return NULL;
    }

    rc = init_class(class, class_type, info, stats, bonus);

    if(rc != 0)
    {
        fprintf(stderr,"Could not initialize class\n");
        return NULL;
    }

    return class;
}


/* See battle_classes.h */
/* temp broken
int class_free(class_t *class)
{
    assert(class != NULL);

    free(class);

    return 0;
}
*/


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
    class_t *test_bard = new_class(CLASS_BARD, bard_des, STAT_CHARISMA, 2.0);
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
    class_t *test_cleric = new_class(CLASS_CLERIC, cleric_des,
                                     STAT_STRENGTH, 2.0);
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
    class_t *test_paladin = new_class(CLASS_PALADIN, paladin_des,
                                      STAT_DEXTERITY, 2.0);
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
    class_t *test_wizard = new_class(CLASS_WIZARD, wizard_des,
                                     STAT_SPEED, 2.0);
    return test_wizard;
}
