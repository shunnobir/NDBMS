CC=clang-10
CFLAGS=-Wall -Wextra -pedantic -std=c17

main:
	$(CC) $(CFLAGS) -o ~/repos/studentDB_c/bin/main main.c

run:
	~/repos/studentDB_c/bin/main

clean:
	rm ~/repos/studentDB_c/bin/main
