VENDOR=vendor/stb.c
TCOD=libtcod/logging.c libtcod/error.c libtcod/bresenham_c.c libtcod/fov_circular_raycasting.c libtcod/fov_permissive2.c libtcod/fov_diamond_raycasting.c libtcod/fov_symmetric_shadowcast.c libtcod/fov_restrictive.c libtcod/fov_recursive_shadowcasting.c libtcod/fov_c.c

all:
	gcc -I/usr/include/lua5.1 -Ivendor $(VENDOR) $(TCOD) fallen_tcod.c -fPIC -shared -o fallen_tcod.so
