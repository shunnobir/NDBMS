CC=clang-10
CFLAGS=-Wall -Wextra -std=c17 -pedantic

DIR=/home/raihan/repos/studentDB_c
SRC=$(DIR)/src/main
STD=$(DIR)/src/studentDB
STD_H=$(DIR)/src/studentDB.h

STDOBJ=$(DIR)/obj/studentDB.o
SRCBIN=$(DIR)/bin/main

$(STDOBJ): $(STD_H)
	$(CC) $(CFLAGS) -c -o $(STDOBJ) $(STD).c

main: $(STDOBJ) $(STD_H)
	$(CC) $(CFLAGS) $(STDOBJ) $(SRC).c -o \
		$(SRCBIN)

clean:
	rm $(STDOBJ)
	rm $(SRCBIN)
