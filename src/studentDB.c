#include <stdio.h>
#include "studentDB.h"


void write_info_f(Data *data, Info *info)
{
    if (data->database) {
        fwrite((void*)info, sizeof(Info), 1, data->database);
        printf("written\n");
    }
}

void write_info(Data *data, Info *info)
{
    data->student[data->entry_ID] = *info;
    /* printf("%s\n%s\n%s\n%s\n%s\n%s\n", data->student[data->entry_ID].ID, */
    /*                                    data->student[data->entry_ID].name, */
    /*                                    data->student[data->entry_ID].department, */
    /*                                    data->student[data->entry_ID].faculty, */
    /*                                    data->student[data->entry_ID].session, */
    /*                                    data->student[data->entry_ID].email); */
    ++data->entry_ID;
}

void read_info_f(Data *data, Info *info)
{
    fread((void*)info, sizeof(Info), 1, data->database);
}

Info *read_info(Data *data, ID_t entry_ID, Info *info)
{
    *info = data->student[entry_ID];
    
    return info;
}

void create_data(Data *data, char *name)
{
    data->entry_ID = 0;
    data->database = fopen(name, "ab");
}

void load_data(Data *data, Mode mode, char *name)
{
    char fname[120] = "/";
    strcat(fname, "home/raihan/repos/studentDB_c/database/");
    strcat(fname, name);

    if (mode == 'c') {
        create_data(data, fname);
    } else if (mode == 'l') {
        data->database = fopen(fname, "rb");
        if (data->database) {
            ID_t entry_ID = 0;
            fread((void*)&entry_ID, sizeof(ID_t), 1, data->database);
            if (entry_ID > 50) {
                fprintf(stderr, "Entry ID is corrupted\n");
            }

            data->entry_ID = entry_ID;
            for (ID_t id = 0; id < entry_ID ; ++id) {
                Info info;
                read_info_f(data, &info);
                data->student[id] = info; 
            }
        } else {
            fprintf(stderr, "Failed to open database file\n");
        }
    }
}

void close_data_c(Data *data)
{
    printf("Writing\n");
    ID_t entry_ID = data->entry_ID;
    fwrite((void*)&entry_ID, sizeof(ID_t), 1, data->database);

    for (ID_t id = 0; id < data->entry_ID; ++id) {
        Info info = data->student[id];
        write_info_f(data, &info);
    }

    fclose(data->database);
}

void close_data_l(Data *data)
{
    if (data->database) {
        fclose(data->database);
    } else {
        fprintf(stderr, "Failed to close database file\n");
    }
}
