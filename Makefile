CFLAGS=-I/usr/include/lua5.1 -Ivendor
MINGW_FLAGS=-Ilualib/include -Ivendor
MINGW_LDFLAGS=-Llualib -llua5.1

VENDOR=vendor/stb.c
TCOD=logging.c error.c bresenham_c.c fov_circular_raycasting.c fov_permissive2.c fov_diamond_raycasting.c fov_symmetric_shadowcast.c fov_restrictive.c fov_recursive_shadowcasting.c fov_c.c

SOURCES=$(VENDOR) $(TCOD) fallen_tcod.c

all:
	x86_64-w64-mingw32-gcc -Ilualib/include -Ivendor -c logging.c -o logging.o
	x86_64-w64-mingw32-gcc -Ilualib/include -Ivendor -c error.c -o error.o
	x86_64-w64-mingw32-gcc -Ilualib/include -Ivendor -c bresenham_c.c -o bresenham_c.o
	x86_64-w64-mingw32-gcc -Ilualib/include -Ivendor -c fov_circular_raycasting.c -o fov_circular_raycasting.o
	x86_64-w64-mingw32-gcc -Ilualib/include -Ivendor -c fov_permissive2.c -o fov_permissive2.o
	x86_64-w64-mingw32-gcc -Ilualib/include -Ivendor -c fov_diamond_raycasting.c -o fov_diamond_raycasting.o
	x86_64-w64-mingw32-gcc -Ilualib/include -Ivendor -c fov_symmetric_shadowcast.c -o fov_symmetric_shadowcast.o
	x86_64-w64-mingw32-gcc -Ilualib/include -Ivendor -c fov_restrictive.c -o fov_restrictive.o
	x86_64-w64-mingw32-gcc -Ilualib/include -Ivendor -c fov_recursive_shadowcasting.c -o fov_recursive_shadowcasting.o
	x86_64-w64-mingw32-gcc -Ilualib/include -Ivendor -c fov_c.c -o fov_c.o
	x86_64-w64-mingw32-gcc -Ilualib/include -Ivendor -c vendor/stb.c -o vendor/stb.o
	x86_64-w64-mingw32-gcc -Ilualib/include -Ivendor -c fallen_tcod.c -o fallen_tcod.o
	x86_64-w64-mingw32-gcc -shared -DBUILD_DLL -o fallen_tcod.dll logging.o error.o bresenham_c.o fov_circular_raycasting.o fov_permissive2.o fov_diamond_raycasting.o fov_symmetric_shadowcast.o fov_restrictive.o fov_recursive_shadowcasting.o fov_c.o vendor/stb.o fallen_tcod.o -Llualib -llua5.1 -Wl,--out-implib,libfallen_tcod.a

linux:
	gcc $(CFLAGS) $(SOURCES) -fPIC -shared -o fallen_tcod.so
	
