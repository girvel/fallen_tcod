#include <lua.h>
#include <lauxlib.h>
#include "libtcod/fov.h"

typedef struct {
    int x;
    int y;
} Vector;

typedef struct {
    TCOD_Map *inner;
} MapContainer;

static int l_add(lua_State *L) {
    int a = luaL_checkinteger(L, 1);
    int b = luaL_checkinteger(L, 2);

    lua_pushinteger(L, a + b);

    return 1;
}

static int l_create_vector(lua_State *L) {
    int x = luaL_checkint(L, 1);
    int y = luaL_checkint(L, 2);

    Vector *v = (Vector *)lua_newuserdata(L, sizeof(Vector));
    luaL_getmetatable(L, "Vector");
    lua_setmetatable(L, -2);
    v->x = x;
    v->y = y;
    return 1;
}

static int l_get_x(lua_State *L) {
    luaL_checktype(L, 1, LUA_TUSERDATA);
    Vector *v = (Vector *)luaL_checkudata(L, 1, "Vector");
    lua_pushinteger(L, v->x);
    return 1;
}

static MapContainer *checkmap(lua_State *L, int index) {
    luaL_checktype(L, index, LUA_TUSERDATA);
    return (MapContainer *)luaL_checkudata(L, 1, "MapContainer");
}

static int l_map_create(lua_State *L) {
    int w = luaL_checkint(L, 1);
    int h = luaL_checkint(L, 2);

    MapContainer *v = (MapContainer *)lua_newuserdata(L, sizeof(MapContainer));
    luaL_getmetatable(L, "MapContainer");
    lua_setmetatable(L, -2);

    v->inner = TCOD_map_new(w, h);
    return 1;
}

static int l_map_set_properties(lua_State *L) {
    MapContainer *m = checkmap(L, 1);
    int x = luaL_checkint(L, 2);  // TODO validize
    int y = luaL_checkint(L, 3);
    bool transparent = lua_toboolean(L, 4);
    bool walkable = lua_toboolean(L, 5);
    
    TCOD_map_set_properties(m->inner, x, y, transparent, walkable);

    return 1;
}

static int l_map_get_transparency(lua_State *L) {
    MapContainer *m = checkmap(L, 1);
    int x = luaL_checkint(L, 2);  // TODO validize
    int y = luaL_checkint(L, 3);

    lua_pushboolean(L, m->inner->cells[x + y * m->inner->width].transparent);

    return 1;
}

static const struct luaL_Reg fallen_tcod[] = {
    {"add", l_add},
    {"create_vector", l_create_vector},
    {"get_x", l_get_x},
    {"map_create", l_map_create},
    {"map_set_properties", l_map_set_properties},
    {"map_get_transparency", l_map_get_transparency},
    {NULL, NULL},
};

int luaopen_fallen_tcod(lua_State *L) {
    luaL_newmetatable(L, "Vector");
    luaL_newmetatable(L, "MapContainer");
    luaL_register(L, "fallen_tcod", fallen_tcod);
    return 1;
}

