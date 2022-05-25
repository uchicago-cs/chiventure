/*
 * A file containing the 2021 demo for the playerclass component.
 */

#include <stdio.h>

#include "playerclass/class_structs.h"
#include "playerclass/class_prefabs.h"
#include "playerclass/class_item.h"
#include "skilltrees/skilltree.h"
#include "zip.h"
#include "libobj/load.h"
#include "wdl/load_game.h"


/* A helper function for printing a class. */
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
            printf("    %s\n", class->parent_class_names[i]);
        }
    }
    else {
        printf("Basic Class\n");
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
    if (class->skilltree != NULL) {
        printf("Skill Tree: \n");
        for (int i = 0; i < class->skilltree->num_nodes; i++) {
            /* This could also be improved */
            printf("    %s\n", class->skilltree->nodes[i]->skill->name);
        }
    }
    else {
        printf("Skill Tree: NULL\n");
    }
    
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

/* This path expects that we are at the root of the build directory */
#define CLASSES_WDL_PATH "../tests/wdl/examples/wdl/classes.wdl"

/* Helper function appropriated from WDL tests to load in a file */
static obj_t *get_doc_obj()
{
    char zip_name[10 * (MAXLEN_ID + 1)] = {0};
    strcat(zip_name, "./");
    strcat(zip_name, "zip_default.zip");

    // Create the zip
    int error = 0;
    zip_t *zip = zip_open(zip_name, ZIP_CREATE | ZIP_TRUNCATE, &error);

    // Add DEFAULT.json to the zip
    char *data_name = "DEFAULT.json";
    char *data_path = CLASSES_WDL_PATH; // Edited to load the example file with classes

    zip_error_t err = {0};
    zip_source_t *zip_src = zip_source_file_create(data_path, 0, 0, &err);

    zip_int64_t idx = zip_file_add(zip, data_name, zip_src, ZIP_FL_ENC_UTF_8);

    // Write and save to disk
    int rc = zip_close(zip);
    zip_error_t *close = zip_get_error(zip);

    int open_status;
    zip = zip_open(zip_name, 0, &open_status);

    // Read the zip into an obj
    obj_t *obj = obj_new("doc");
    rc = load_obj_store_from_zip(obj, zip);

    return obj;
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

void demo_WDL() {
    /* This is basically an interactive version of the tests, showing the different 
     * kinds of classes you can laod */
    obj_t *obj_store = get_doc_obj();
    game_t *game = load_game(obj_store);

    /* If the game is NULL, then the WDL example file could not be found. */
    if (game == NULL) {
        printf("ERROR! Game object is NULL.\nMake sure to run this executable " 
               "in root of the build directory so it can properly find the "
               "example WDL file.\nAborting demo_WDL().\n");
        return;
    }

    printf("Game successfully loaded from WDL File: %s\n", CLASSES_WDL_PATH);

    prompt("Loading Knight class, fully defined in the file...", NULL);
    print_class(find_class(&game->all_classes, "Knight"));
    
    prompt("Loading Rogue class, partially defined in the file...", NULL);
    print_class(find_class(&game->all_classes, "Rogue"));
    
    prompt("Loading Monk class, a prefab class declared in the file...", NULL);
    print_class(find_class(&game->all_classes, "Monk"));
    
    prompt("Loading Warrior class, a partially overwritten prefab class declared in the file...", NULL);
    print_class(find_class(&game->all_classes, "Warrior"));
}

void demo_multiclasses() {
    game_t* game = game_new("The playerclass demo game!");

    prompt("Loading Wizard class, a prefab class...", NULL);
    class_t* wizard_class = class_prefab_new(game, "Wizard");
    class_prefab_add_skills(wizard_class);
    print_class(wizard_class);

    prompt("Loading Warrior class, a prefab class...", NULL);
    class_t* warrior_class = class_prefab_new(game, "Warrior");
    class_prefab_add_skills(warrior_class);
    print_class(warrior_class);

    prompt("Creating a new multiclass called Hexblade from Wizard and Warrior...", NULL);
    class_t* hexblade_class = multiclass(wizard_class, warrior_class, "Hexblade");
    print_class(hexblade_class);
}

void demo_item_interactions() {
    /* This is a basic implementation, appropriating ideas from pc-demo.c */
    game_t* game = game_new("The playerclass demo game!");

    class_t* wizard = class_prefab_new(game, "Wizard");
    class_t* bard = class_prefab_new(game, "Bard");
    class_t* warrior = class_prefab_new(game, "Warrior");

    item_t* wand = item_new("wand", " ", " ");
    item_t* sword = item_new("sword", " ", " ");
    item_t* guitar = item_new("guitar", " "," ");

    /* Item Restrictions */
    prompt("Adding Item restriction: The Wizard can't use a sword.", NULL);
    add_item_restriction(sword, wizard);

    bool allowed_sword = is_restricted(sword, wizard);
    prompt("You are now playing with class Wizard. Your task is to find a weapon to defeat your archenemy.", NULL);
    printf("You find a sword lying on a rock, and you are %s to use it.\n", 
           allowed_sword? "unable": "able");

    prompt("Switching to class Bard...", NULL);

    allowed_sword = is_restricted(sword, bard);
    printf("%s You are now %s to use the sword.\n", allowed_sword? "Failure.": "Success!", allowed_sword? "unable": "able");
    printf("The sword %s been added to the inventory, and you continue onwards.", allowed_sword? "hasn't": "has");
    prompt("", NULL);

    /* Item modifiers */
    prompt("Adding Item multipliers: The Bard is naturally bad at using the wand. The Wizard is naturally good.", NULL);
    add_item_multiplier(wand, wizard, 1.5);
    add_item_multiplier(wand, bard, 0.5);
    add_item_restriction(wand, warrior);

    prompt("You encounter an evil Goblin. To move forward, you must charm the Goblin by casting a spell.", NULL);
    double mult = get_class_item_multiplier(wand, bard);
    printf("You attempt to cast the spell, but you can only use the wand at %.2fx its effectiveness.\n", mult);
    prompt("You have failed to charm the evil Goblin.", NULL);
    prompt("Switching to class Wizard...", NULL);
    mult = get_class_item_multiplier(wand, wizard);
    printf("Wow! You used the wand at %.2fx its effectiveness and charmed the Goblin.\n", mult);
}


/* Due to having to locate the example WDL file, it is critical that this executable 
 * is run from from a specific location: the root of the build/ directory. Running it anywhere else will cause 
 * it to fail to find the WDL file, leading to segfaults. 
 * 
 * I prefer to use the command: 
 * $ make examples && src/playerclass/examples/2021-demo */

/* main function for the 2021-demo executable. */
int main() {
    /* We decided to break up the ~10 minute demo into 2-3 minute mini demos */
    printf("***Entering prefab mini-demo***\n");
    demo_prefab_classes();
    
    printf("***Entering WDL mini-demo***\n");
    demo_WDL();

    printf("***Entering multiclass mini-demo***\n");
    demo_multiclasses();

    printf("***Entering item interactions mini-demo***\n");
    demo_item_interactions();
}
