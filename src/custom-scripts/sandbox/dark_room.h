#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"

typedef struct torch {
bool state; // on or off?
} torch_t;