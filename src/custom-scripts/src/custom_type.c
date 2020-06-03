#include "custom-scripts/custom_type.h"

// see custom_type.h
arg_t *arg_t_new() {
    arg_t *arg = (arg_t*)malloc(sizeof(arg_t));
    arg->type = NONE_TYPE;
    arg->next = NULL;
    return arg;
}

// see custom_type.h
arg_t *arg_t_bool(bool b) {
    arg_t *arg = arg_t_new();
    arg->type = BOOL_TYPE;
    arg->data.b = b;
    return arg;
}

// see custom_type.h
void arg_t_add(arg_t *head, arg_t *add) {
    arg_t *temp = head;
    // iterating over linked list to last node
    while(temp->next) {
        temp = temp->next;
    }
    temp->next = add;
}

// see custom_type.h
object_t *obj_t_new()
{
    object_t *ot = (object_t*)malloc(sizeof(object_t));
    ot->type = NONE_TYPE;
    ot->is_lua = false;
    ot->args = NULL;
    return ot;
}

// see custom_type.h
object_t *obj_t_bool(bool b, char *lua, arg_t* head)
{
    object_t *ot = obj_t_new();
    ot->type = BOOL_TYPE;
    if (lua) {
        ot->is_lua = true;
        ot->data.lua = lua;
        ot->args = head;
    } else {
        ot->data.b = b;
    }
    return ot;
}

// see custom_type.h
object_t *obj_t_char(char c, char *lua)
{
    object_t *ot = obj_t_new();
    ot->type = CHAR_TYPE;
    if (lua) {
        ot->is_lua = true;
        ot->data.lua = lua;
    } else {
        ot->data.c = c;
    }
    return ot;
}

// see custom_type.h
object_t *obj_t_int(int i, char *lua)
{
    object_t *ot = obj_t_new();
    ot->type = INT_TYPE;
    if (lua) {
        ot->is_lua = true;
        ot->data.lua = lua;
    } else {
        ot->data.i = i;
    }
    return ot;
}

// see custom_type.h
object_t *obj_t_str(char *s, char *lua)
{
    object_t *ot = obj_t_new();
    ot->type = STR_TYPE;
    if (lua) {
        ot->is_lua = true;
        ot->data.lua = lua;
    } else {
        ot->data.s = s;
    }
    return ot;
}

/**
 * Helper function used to push the arguments in the linked list
 * to the Lua vritual stack
 * Returns the number of arguments in the linked list
 */
int push_args(lua_State *L, object_t* ot) {
    int count = 0;
    arg_t *head = ot->args;
    data_type_t type = ot->type;
    while (head != NULL) {
        // incrememnt argument count
        count++;

        // push argument to virtual stack
        switch(type) {
            case BOOL_TYPE:
            {
                int b = ot->data.b; // pushboolean requires int
                lua_pushboolean(L, b);
                break;
            }
            case CHAR_TYPE:
                break;
            case INT_TYPE:
                break;
            case STR_TYPE:
                break;
            default: // NONE_TYPE
                break;
        }

        // move to next argument
        head = head->next;
    }
    return count;
}


/**
 * Helper function for the getter functions below
 * Calls the Lua function in the directory specified, stores the data
 * in the Lua virtual stack for the getter functions to extract and return
 */
lua_State *callLua(object_t *ot, char *lua_path) {
    lua_State *L = luaL_newstate();

    // opens all standard Lua libraries into the given state
    luaL_openlibs(L);

    // loads the given file
    luaL_dofile(L, lua_path);

    // sets virtual stack top to index 0
    lua_settop(L, 0);

    // push functions and arguments
    lua_getglobal(L, "foo");
    int num_args = push_args(L, ot);
    lua_pcall(L, num_args, 1, 0);

    return L;
}

// see custom_types.h
bool bool_t_get(object_t *ot) {
    assert(ot->type == BOOL_TYPE);
    if (ot->is_lua) {
        char *lua_path = ot->data.lua;
        lua_State *L = callLua(ot, lua_path);
        int result = (int)lua_toboolean(L, -1);
        lua_pop(L, 1);
        if (result)
            return true;
        else
            return false;
    } 
    else {
        return ot->data.b;
    }
}

// see custom_types.h
char char_t_get(object_t *ot) {
    assert(ot->type == CHAR_TYPE);
    if (ot->is_lua) {
        char *lua_path = ot->data.lua;
        lua_State *L = callLua(ot, lua_path);
        const char *result = lua_tostring(L, -1);
        lua_pop(L, 1);
        char *result1 = strdup(result);
        return *result1;
    } else {
        return ot->data.c;
    }
}

// see custom_types.h
int int_t_get(object_t *ot) {
    assert(ot->type == INT_TYPE);
    if (ot->is_lua) {
        char *lua_path = ot->data.lua;
        lua_State *L = callLua(ot, lua_path);
        int result = (int)lua_tointeger(L, -1);
        lua_pop(L, 1);
        return result;
    } else {
        return ot->data.i;
    }
}

// see custom_types.h
char* str_t_get(object_t *ot) {
    assert(ot->type == STR_TYPE);
    if (ot->is_lua) {
        char *lua_path = ot->data.lua;
        lua_State *L = callLua(ot, lua_path);
        const char *result = lua_tostring(L, -1);
        lua_pop(L, 1);
        char *result1 = strdup(result);
        return result1;
    } else {
        return ot->data.s;
    }
}