#include "cli/cli-utility.h"

// This is specifically for functions meant to be used
// across the entire game state, either for formatting
// or for other broad changes that need to be addressed



/* See cli-utility.h */
void case_insensitize1(char *input)
{
    int i = 0;
    char c;
    while (input[i])
    {
        c = tolower(input[i]);
        input[i] = c;
        i++;
    }
}


/* See cli-utility.h */
char* case_insensitize2(char *input)
{
    char* output = malloc(sizeof(char) * strnlen(input, 100));
    for(int i = 0; i < strnlen(input, 100); i++)
    {
        output[i] = tolower(input[i]);
    }

    return output;
}