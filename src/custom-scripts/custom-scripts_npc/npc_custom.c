#include "game-state/npc.h"
#include "common-item.h"
#include "lauxlib.h"
#include <stdlib.h>
#include <stdio.h> 
#include "lua.h"
#include "lualib.h"

int lua_npc(npc_t *example_npc)
{

assert(example_npc);
char* string = mallo(BUFFER_SIZE);
memset(string, 0, BUFFER_SIZE);
int a;

printf("Apply LUA functions?");
printf("Press 1 -- automatically kill NPC, 2 -- automatically revive NPC, 3 -- half health to NPC);
scanf("%d", &a);

lua_State* L = lua_newstate();
luaL_openlibs(L);
luaL_dofile(L, "npc_scripts.lua");
lua_settop(L,0);

lua_getglobal(L,"health_modify");
lua_pushnumber(L, a);
lua_pushnumber(L, example_npc->health);
lua_call(L, 2, 1);

int result = (int)lua_tointeger(L, -1);
lua_pop(L, 1);
return result;
}

int main()
{
int result = lua_npc(npc_t *example_npc)
return 0;
}
