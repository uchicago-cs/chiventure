/*
 * A file containing the 2021 demo for the playerclass component.
 */

#include <stdio.h>

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
    /* test code */
    char name[BUFFER_SIZE]; 
    prompt("What is your name?", name); 
    printf("Hello, %s!\n", name);
}
