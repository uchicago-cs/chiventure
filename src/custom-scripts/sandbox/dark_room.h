#include <stdlib.h> 
#include <stdio.h>
#include <stdbool.h>
#include "lua/lauxlib.h"
#include "lua/lua.h"
#include "lua/lualib.h"

typedef struct torch {
bool state; // on or off?
} torch_t;