#include <stdbool.h>
#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"

typedef struct torch {
    bool state; // false = unlit, true = lit
} torch_t;