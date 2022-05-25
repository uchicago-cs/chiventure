#include <stdlib.h> 

int main() {

  lua_State *L = luaL_newstate();
  luaL_openlibs(L);
  luaL_dofile(L, "sample.lua");
  lua_settop(L, 0);

  torch_t* t = malloc(sizeof(torch_t));

  t->state = false;

    printf("the torch is currently %s\n", t->state ? "lit" : "unlit")
      // Push the "flip" function on the top of the lua stack
    lua_getglobal(L, "flip");

    // Push the argument (the "false" state of the torch) on the stack 
    lua_pushboolean(L, t->state);

    // call the function with 1 argument, returning a single result.  Note that the function actually
    // returns 2 results -- we just want one of them.  
    lua_call(L, 1, 1);

    // Get the result from the lua stack
    bool result = (bool)lua_tobool(L, -1);
    t->state = result;
    printf ("Observe that after the call to Lua the torch is now %s!\n", t->state ? "lit" : "unlit");

    // Clean up.  If we don't do this last step, we'll leak stack memory.
    lua_pop(L, 1);

  return 0;
}