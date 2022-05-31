/*
 * A file containing the 2022 demo for the playerclass component.
 */

#include <stdio.h>

#include "playerclass/class_structs.h"
#include "playerclass/class_prefabs.h"
#include "playerclass/class_item.h"
#include "playerclass/multiclass.h"
#include "playerclass/multiclass_prefabs.h"
#include "skilltrees/skilltree.h"
#include "zip.h"
#include "libobj/load.h"
#include "wdl/load_game.h"


/* A helper function for printing a skilltree.
 *
 * Parameters:
 *  - skilltree: the tree to be printed
 * 
 * Returns:
 *  - nothing, just prints information
*/
void print_skilltree(skill_tree_t* skilltree) {

    /* Skill Tree */
    if (skilltree != NULL) {
        printf("Skill Tree: \n");
        for (int i = 0; i < skilltree->num_nodes; i++) {
            
            /* Name */
            if (skilltree->nodes[i]->skill->name != NULL) {
                printf("    %s\n", skilltree->nodes[i]->skill->name);
            }
            else {
                printf("    Skill Name: NULL.\n");
            }

            /* Description */
            if (skilltree->nodes[i]->skill->name != NULL) {
                printf("        Description: %s\n", 
                        skilltree->nodes[i]->skill->desc);
            }
            else {
                printf("        Description: NULL.\n");
            }

            /* Type */
            printf("        Type: ");
            switch (skilltree->nodes[i]->skill->type) {
                case PLAYER_STATISTIC_MOD:
                    printf("Player Statistic Mod\n");
                    break;
                case MOVE_UNLOCK:
                    printf("Move Unlock\n");
                    break;
                case ITEM_ATTRIBUTE_MOD:
                    printf("Item Attribute Mod\n");
                    break;
                case ITEM_STATISTIC_MOD:
                    printf("Item Statistic Mod\n");
                    break;
            }

            /* Minimum XP */
            printf("        Minimum XP: %u\n", 
                    skilltree->nodes[i]->skill->min_xp);

            /* Maximum level */
            printf("        Maximum level: %u\n", 
                    skilltree->nodes[i]->skill->max_level);
        }
    }
    else {
        printf("Skill Tree: NULL\n");
    }

}


/* A helper function for printing a class.
 *
 * Parameters:
 *  - class: the class to be printed
 * 
 * Returns:
 *  - nothing, just prints information
*/
void print_class(class_t* class) {
    printf("------------------------------------------------------------\n");

    if (class == NULL) {
        printf("Class is NULL.\n");
        printf("------------------------------------------------------------\n");
        return;
    }

    /* Name */
    if (class->name != NULL) {
        printf("Name: %s\n", class->name);
    }
    else {
        printf("Name: NULL.\n");
    }

    /* Multiclass info */
    if (class->num_parent_class > 0) {
        printf("Multiclass with parents: \n");
        for (int i = 0; i < class->num_parent_class; i++) {
            printf("Parent Class %d: %s\n", i+1, class->parent_class_names[i]);
        }
    }
    else {
        printf("Single Class\n");
    }

    /* Short Description */
    if (class->shortdesc != NULL) {
        printf("Short Description: %s\n", class->shortdesc);
    }
    else {
        printf("Short Description: NULL\n");
    }

    /* Long Description */
    if (class->longdesc != NULL) {
        printf("Long Description: %s\n", class->longdesc);
    }
    else {
        printf("Long Description: NULL\n");
    }

    /* Attributes */
    if (class->attributes != NULL) {
        printf("Attributes:\n");
        dump_obj(class->attributes);
    }
    else {
        printf("Attributes: NULL\n");
    }

    /* Stats */
    if (class->base_stats != NULL) {
        printf("Base Stats: \n");
        stats_t *stat, *tmp;
        HASH_ITER(hh, class->base_stats, stat, tmp) {
            printf("    %s: %.2f / %.2f\n", stat->key, stat->val, stat->global->max);
        }
    }
    else {
        printf("Base Stats: NULL\n");
    }

    /* Effects */
    if (class->effects != NULL) {
        printf("Effects: \n");
        stat_effect_t *effect, *tmp;
        HASH_ITER(hh, class->effects, effect, tmp) {
            /* This could be improved to print more info, but this should suffice for now */
            printf("    %s", effect->key);
        }
    }
    else {
        printf("Effects: NULL\n");
    }

    /* Skill Tree */
    print_skilltree(class->skilltree);
    
    /* Starting Skills */
    if (class->starting_skills != NULL) {
        printf("Starting Skills: \n");
        for (int i = 0; i < class->starting_skills->num_active; i++) {
            printf("    %s\n", class->starting_skills->active[i]->name);
        }
        for (int i = 0; i < class->starting_skills->num_passive; i++) {
            printf("    %s\n", class->starting_skills->passive[i]->name);
        }
    }
    else {
        printf("Starting Skills: NULL\n");
    }

    printf("------------------------------------------------------------\n");
}


#define BUFFER_SIZE 100

/* A helper function for pausing execution and asking for input. 
 * 
 * Parameters:
 *  - message: The message that will be printed out as a prompt (newline is added).
 *  - input: Pointer to memory to store the input, or NULL (in which case input is ignored).
 * 
 * Returns:
 *  - Nothing.
 */
void prompt(char* message, char* input) {
    printf("%s\n>>> ", message);

    if (input != NULL) {
        fgets(input, BUFFER_SIZE, stdin);

        /* Delete trailing newline */
        char* ch_ptr = input;
        while (*ch_ptr != '\n') {
            ch_ptr += sizeof(char);
        }
        *ch_ptr = '\0'; 
    }
    else {
        char ignore[BUFFER_SIZE];
        fgets(ignore, BUFFER_SIZE, stdin);
    }
}

/* The following functions are demo functions.  Feel free to loop and prompt for 
 * input, just remember to make it possible to escape these functions. */

void demo_prefab_classes() {
    game_t* game = game_new("The playerclass demo game!");

    /* Runs until you input nothing. */
    char class_name[BUFFER_SIZE];
    while (true) {
        prompt("Pick a prefab class:", class_name);
        if (class_name[0] == '\0') {
            break;
        }
        class_t* class = class_prefab_new(game, class_name);
        if (class != NULL) {
            class_prefab_add_skills(class);
        }
        print_class(class);
    }
}

void demo_multiclasses() {
    game_t* game = game_new("The playerclass demo game!");


    /* Runs until you input nothing. */
    char class_name[BUFFER_SIZE];
    while (true) {
        prompt("Pick a prefab multiclass:", class_name);
        if (class_name[0] == '\0') {
            break;
        }
        class_t* class = multiclass_prefab_new(game, class_name);
        printf("------------------");
        if (class != NULL) {
            multiclass_prefab_add_skills(game, class);
        }
        print_class(class);
    }
}


/* In the build directory, use the command: 
 * $ make examples && src/playerclass/examples/2022-demo */

/* main function for the 2022-demo executable. */
int main() {
    /* We broke up the demo into two mini demos */
    printf("***Entering prefab mini-demo***\n\n\n");
    demo_prefab_classes();

    printf("***Entering multiclass mini-demo***\n");
    demo_multiclasses();
}
