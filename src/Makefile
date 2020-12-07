CC=clang-10
CFLAGS=-Wall -Wextra -std=c17 -pedantic

DIR=/home/raihan/repos/studentDB_c
SRC=main
STD=studentDB
STDOBJ=$(DIR)/obj/$(STD).o

$(STDOBJ): $(STD).h
	$(CC) $(CFLAGS) -c -o $(STDOBJ) $(STD).c

main: $(STDOBJ) $(STD).h
	$(CC) $(CFLAGS) $(STDOBJ) $(SRC).c -o $(SRC)

clean:
	rm $(DIR)/obj/*
	rm $(DIR)/src/$(SRC)
