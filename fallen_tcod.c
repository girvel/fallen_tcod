#include <lua.h>
#include <lauxlib.h>

static int l_add(lua_State *L) {
    int a = luaL_checkinteger(L, 1);
    int b = luaL_checkinteger(L, 2);

    lua_pushinteger(L, a + b);

    return 1;
}

static const struct luaL_Reg fallen_tcod[] = {
    {"add", l_add},
    {NULL, NULL},
};

int luaopen_fallen_tcod(lua_State *L) {
    luaL_register(L, "fallen_tcod", fallen_tcod);
    return 1;
}

