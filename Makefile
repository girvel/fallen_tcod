all:
	gcc -I/usr/include/lua5.1 fallen_tcod.c -c -fPIC
	gcc fallen_tcod.o -shared -o fallen_tcod.so
