CFLAGS=-I/usr/include/lua5.1 -Ivendor
MINGW_FLAGS=-Ilualib/include -Ivendor
MINGW_LDFLAGS=-Llualib -llua5.1

VENDOR=vendor/stb.c
TCOD=libtcod/logging.c libtcod/error.c libtcod/bresenham_c.c libtcod/fov_circular_raycasting.c libtcod/fov_permissive2.c libtcod/fov_diamond_raycasting.c libtcod/fov_symmetric_shadowcast.c libtcod/fov_restrictive.c libtcod/fov_recursive_shadowcasting.c libtcod/fov_c.c

SOURCES=$(VENDOR) $(TCOD) fallen_tcod.c

all:
	x86_64-w64-mingw32-gcc $(MINGW_FLAGS) -shared -DBUILD_DLL -Wl,--out-implib,libfallen_tcod.a $(SOURCES) -o fallen_tcod.dll $(MINGW_LDFLAGS)

linux:
	gcc $(CFLAGS) $(SOURCES) -fPIC -shared -o fallen_tcod.so
	
