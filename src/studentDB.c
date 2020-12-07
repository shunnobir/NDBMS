#include <stdio.h>
#include "studentDB.h"


void write_info(Data *data, Info *info)
{
    if (data->database) {
        fwrite((void*)info, sizeof(Info), 1, data->database);
        ++data->entry_ID;
    }
    fflush(data->database);
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
    if (mode == 'c') {
        create_data(data, name);
    } else if (mode == 'l') {
        /* printf("Loading\n"); */
        FILE *internal_info = fopen("info.txt", "r");
        if (internal_info) {
            ID_t total_entry = 0;
            fread((void*)(&total_entry), sizeof(ID_t), 1, internal_info);
            /* printf("Entry: %zu\n", total_entry); */
            fclose(internal_info);

            data->database = fopen(name, "rb");
            data->entry_ID = total_entry;
            if (data->database) {
                /* printf("opening database\n"); */
                for (ID_t id = 0; id < total_entry; ++id) {
                    /* printf("reading one by one\n"); */
                    read_info_f(data, &data->student[id]); 
                }
            } else {
                fprintf(stderr, "Failed to open %s\n", name);
            }
        } else {
            fprintf(stderr, "Failed to open info.txt");
        }
    }
}

void close_data(Data *data)
{
    /* printf("Closing\n"); */
    FILE *internal_info = fopen("info.txt", "w");
    if (internal_info) {
        /* printf("Writing %zu\n", data->entry_ID); */
        ID_t id = data->entry_ID;
        fwrite((void*)(&id), sizeof(ID_t), 1, internal_info);
        fflush(internal_info);
        fclose(internal_info);

        fclose(data->database);
    } else {
        fprintf(stderr, "Failed to open info.txt\n");
    }
}


