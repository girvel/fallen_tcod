#include <lua.h>
#include <lauxlib.h>
#include "fov.h"

#ifdef BUILD_DLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllimport)
#endif

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

static int l_map_is_transparent(lua_State *L) {
    MapContainer *m = checkmap(L, 1);
    int x = luaL_checkint(L, 2);  // TODO validize
    int y = luaL_checkint(L, 3);
    
    lua_pushboolean(L, TCOD_map_is_transparent(m->inner, x, y));

    return 1;
}

static int l_map_is_walkable(lua_State *L) {
    MapContainer *m = checkmap(L, 1);
    int x = luaL_checkint(L, 2);  // TODO validize
    int y = luaL_checkint(L, 3);
    
    lua_pushboolean(L, TCOD_map_is_walkable(m->inner, x, y));

    return 1;
}

static int l_map_is_in_fov(lua_State *L) {
    MapContainer *m = checkmap(L, 1);
    int x = luaL_checkint(L, 2);  // TODO validize
    int y = luaL_checkint(L, 3);
    
    lua_pushboolean(L, TCOD_map_is_in_fov(m->inner, x, y));

    return 1;
}

static int l_map_compute_fov(lua_State *L) {
    MapContainer *m = checkmap(L, 1);
    int player_x = luaL_checkint(L, 2);
    int player_y = luaL_checkint(L, 3);
    int max_radius = luaL_checkint(L, 4);
    bool light_walls = lua_toboolean(L, 5);
    TCOD_fov_algorithm_t algorithm = (TCOD_fov_algorithm_t) luaL_checkint(L, 6);

    TCOD_map_compute_fov(m->inner, player_x, player_y, max_radius, light_walls, algorithm);

    return 1;
}

static const struct luaL_Reg fallen_tcod[] = {
    {"add", l_add},
    {"create_vector", l_create_vector},
    {"get_x", l_get_x},
    {"map_create", l_map_create},
    {"map_set_properties", l_map_set_properties},
    {"map_is_transparent", l_map_is_transparent},
    {"map_is_walkable", l_map_is_walkable},
    {"map_is_in_fov", l_map_is_in_fov},
    {"map_compute_fov", l_map_compute_fov},
    {NULL, NULL},
};

DLL_EXPORT int luaopen_fallen_tcod(lua_State *L) {
    luaL_newmetatable(L, "Vector");
    luaL_newmetatable(L, "MapContainer");
    luaL_register(L, "fallen_tcod", fallen_tcod);
    return 1;
}

