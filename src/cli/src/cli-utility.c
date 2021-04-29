#include "cli/cli-utility.h"

// This is specifically for functions meant to be used
// across the entire game state, either for formatting
// or for other broad changes that need to be addressed



/* See game_state_common.h */
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