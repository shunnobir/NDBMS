#ifndef STUDENDB_HDR
#define STUDENDB_HDR

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
/* #include <String.h> */

typedef char String[100];
typedef char Mode;

typedef struct Info {
    String ID;
    String name;
    String department;
    String faculty;
    String session;
    String email;
} Info;

typedef size_t ID_t;
typedef struct Data {
    Info student[10];
    ID_t entry_ID;
    FILE *database;
} Data;

void create_data(Data *data, char *name);
void load_data(Data *data, Mode mode, char *name);
void write_info(Data *data, Info *info);
Info *read_info(Data *data, ID_t entry_ID, Info *info);
void close_data(Data *data);

#endif
