CC=clang-10
CFLAGS=-Wall -Wextra -std=c17 -pedantic

DIR=/home/raihan/repos/studentDB_c
SRC=$(DIR)/src/main
STD=studentDB

STDOBJ=$(DIR)/obj/$(STD).o
SRCBIN=$(DIR)/bin/$(SRC)

$(STDOBJ): $(STD).h
	$(CC) $(CFLAGS) -c -o $(STDOBJ) $(STD).c

main: $(STDOBJ) $(STD).h
	$(CC) $(CFLAGS) $(STDOBJ) $(SRC).c -o $(SRCBIN)

clean:
	rm $(STDOBJ)
	rm $(SRCBIN)
