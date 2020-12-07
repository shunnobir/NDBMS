#include <stdio.h>
#include <stdbool.h>
#include "studentDB.h"
static void get_info(Info *info)
{
    printf("Enter student's ID: ");
    scanf("%s", info->ID);
    getchar();
    printf("Enter student's name: ");
    scanf("%[^\n]", info->name);
    getchar();
    printf("Enter student's department name: ");
    scanf("%[^\n]", info->department);
    getchar();
    printf("Enter student's faculty name: ");
    scanf("%[^\n]", info->faculty);
    getchar();
    printf("Enter student's session: ");
    scanf("%[^\n]", info->session);
    getchar();
    printf("ENter sttudent's email: ");
    scanf("%[^\n]", info->email);
    getchar();
}

static void print_info(Info *info)
{
    printf("ID: %s\n", info->ID);
    printf("Name: %s\n", info->name);
    printf("Department: %s\n", info->department);
    printf("Faculty: %s\n", info->faculty);
    printf("Session: %s\n", info->session);
    printf("Email: %s\n", info->email);
}

int main(void) {
    Data database;
    printf("Choose an option: \n"
           "1. Create New Database\n"
           "2. Open Existing Database\n");
    int option = 0;
    while (scanf("%d", &option) && (option != 1 && option != 2))
        printf("Please enter 1 or 2: ");
    getchar();
    
    if (option == 1) {
        printf("Enter file's name (absolute location is recommended): ");
        char fname[20];
        scanf("%[^\n]", fname);
        load_data(&database, 'c', fname);
        
        while (true) {
            printf("Do you want to make a new entry?\n"
                   "1. yes\t2. No\n");
            while (scanf("%d", &option) && (option != 1 && option != 2))
                printf("Please enter 1 or 2: ");        
            getchar();

            if (option == 1) {
                Info info;
                get_info(&info);
                write_info(&database, &info);
                putchar('\n');
            } else {
                break;
            }
        }
        close_data_c(&database);
    } else {
        printf("Enter the database file name (absolute location is recommended): ");
        char fname[20];
        scanf("%s", fname);
        load_data(&database, 'l', fname);
        for (ID_t id = 0; id < database.entry_ID; ++id) {
            Info info;
            read_info(&database, id, &info);
            print_info(&info);
            putchar('\n');
        }
        close_data_l(&database);
    }

}
