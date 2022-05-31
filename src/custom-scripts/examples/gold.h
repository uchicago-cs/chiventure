#include <stdlib.h> 
#include <stdio.h>
#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"

typedef struct chest
{
    int coins;
} chest_t;