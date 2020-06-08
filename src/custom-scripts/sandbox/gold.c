#include <stdlib.h> 
#include "lua.h"
#include "lualib.h"
#include "gold.h"

/*int luaCoinValue(lua_State* L, int b)
{
lua_pushnumber(L, b);
lua_call(L,1, 1);

int sum = (int)lua_tointeger(L, -1);

lua_pop(L,1);

return sum;
}*/

int main() {

  lua_State *L = luaL_newstate();
  luaL_openlibs(L);
  luaL_dofile(L, "sample.lua");
  lua_settop(L, 0);

  chest_t* t = malloc(sizeof(chest_t));

  t->coins = 0;

    printf("value of chest coins is initially is %d\n", t->coins);
      // Push the change function on the top of the lua stack
    lua_getglobal(L, "change");

    // Push the argument (the number 13) on the stack 
    lua_pushnumber(L, t->coins);

    // call the function with 1 argument, returning a single result.  Note that the function actually
    // returns 2 results -- we just want one of them.  
    lua_call(L, 1, 1);

    // Get the result from the lua stack
    int result = (int)lua_tointeger(L, -1);
    t->coins = result;
    printf ("Result of chest coins after lua is now = %d\n", t->coins);

    // Clean up.  If we don't do this last step, we'll leak stack memory.
    lua_pop(L, 1);

  return 0;
}
