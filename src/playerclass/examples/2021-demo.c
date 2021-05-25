/*
 * A file containing the 2021 demo for the playerclass component.
 */

#include <stdio.h>

#include "playerclass/class_structs.h"
#include "playerclass/class_prefabs.h"


/* A helper function for printing a class. */
void print_class(class_t* class) {
    printf("------------------------------------------------------------\n");

    if (class == NULL) {
        printf("Class is NULL.\n");
        printf("------------------------------------------------------------\n");
        return;
    }

    /* Name */
    if (class->name != NULL) 
        printf("Name: %s\n", class->name);
    else
        printf("Name: NULL.\n");
    
    /* Short Description */
    if (class->shortdesc != NULL)
        printf("Short Description: %s\n", class->shortdesc);
    else
        printf("Short Description: NULL\n");

    /* Long Description */
    if (class->longdesc != NULL)
        printf("Long Description: %s\n", class->longdesc);
    else
        printf("Long Description: NULL\n");

    /* Attributes */
    if (class->attributes != NULL) {
        printf("Attributes:\n");
        dump_obj(class->attributes);
    }
    else
        printf("Attributes: NULL\n");

    printf("------------------------------------------------------------\n");
}

#define BUFFER_SIZE 100

/* A helper function for pausing execution and asking for input. 
 * 
 * Parameters:
 *  - message: The message that will be printed out as a prompt (newline is added).
 *  - buffer: Pointer to memory to store the input, or NULL (in which case input is ignored).
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
        while (*ch_ptr != '\n')
            ch_ptr += sizeof(char);
        *ch_ptr = '\0'; 
    }
    else {
        char ignore[BUFFER_SIZE];
        fgets(ignore, BUFFER_SIZE, stdin);
    }
}

/* main function for the 2021-demo executable. */
int main() {
    game_t* game = game_new("The playerclass demo game!");

    /* test code */

    /* Runs until you input NULL. */
    char class_name[BUFFER_SIZE];
    while (true) {
        prompt("Pick a prefab class:", class_name);
        if (class_name[0] == '\0')
            break;
        class_t* class = class_prefab_new(game, class_name);
        print_class(class);
    }
}
