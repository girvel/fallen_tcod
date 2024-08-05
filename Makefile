all:
	gcc -I/usr/include/lua5.1 add_lib.c -c -fPIC
	gcc -I/usr/include/lua5.1 add_lib.c -shared -o add_lib.so
