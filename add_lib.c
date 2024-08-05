#include <lua.h>
#include <lauxlib.h>

static int l_add(lua_State *L) {
    int a = luaL_checkinteger(L, 1);
    int b = luaL_checkinteger(L, 2);

    lua_pushinteger(L, a + b);

    return 1;
}

static const struct luaL_Reg addlib [] = {
    {"add", l_add},
    {NULL, NULL},
};

int luaopen_add_lib(lua_State *L) {
    luaL_register(L, "addlib", addlib);
    return 1;
}

