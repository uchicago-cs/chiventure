#include "cli/util.h"

// This is specifically for functions meant to be used
// across the entire game state, either for formatting
// or for other broad changes that need to be addressed



/* See util.h */
void case_insensitize(char *input)
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


/* See util.h */
char* case_insensitized_string(char *input)
{
    int len = strlen(input);
    char* output = malloc(sizeof(char) * len + 1);
    for(int i = 0; i < len; i++)
    {
        output[i] = tolower(input[i]);
    }

    output[len] = '\0';
    return output;
}