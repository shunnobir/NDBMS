#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

enum commands {
    LIST, CREATE,
    INSERT, FINISH, 
    LOAD, ADD,
    GET, CLOSE,
    SHOWALL, 
    HELP, EXIT
};

char const *Commands[] = { "list", "create", "insert", "finish", 
                    "load", "add", "get", "close", "show-all", "help", "exit"
                  };

typedef struct Fields {
    char name[34];
    char phone[12];
    char email[34];
} Fields;

typedef struct table {
    uint32_t no_of_records;
    Fields records[20];
} Table;

void help_ndbs();
void command_error(char const *command, void (*help) (void));

void help_list();
void list_database();

void help_create();
void insert_record();
void create_database();

void help_load();
void add_record();
void get_record();
void show_all_records();
void close_database();
void load_database();

void print_command_prompt(char const *command);

bool equal(char const *str1, char const *str2)
{
    return strcmp(str1, str2) == 0;
}

void load_prompt()
{
    printf("ndbs> ");
    print_command_prompt("ndbs");
    char command[7];
    scanf("%s", command);

    while (!equal(command, Commands[EXIT])) {
        if (equal(command, Commands[LIST])) {
            getchar();
            list_database();
        } else if (equal(command, Commands[CREATE])) {
            create_database();
        } else if (equal(command, Commands[LOAD])) {
            getchar();
            load_database();
        } else if (equal(command, Commands[HELP])) {
            getchar();
            help_ndbs();
        } else if (equal(command, Commands[EXIT])){
            getchar();
            return;
        } else {
            getchar();
            command_error(command, help_ndbs);
            return;
        }

        printf("ndbs> ");
        print_command_prompt("ndbs");
        scanf("%s", command);
        /* getchar(); */
    }
}

int main(int argc, char *argv[static 1]) {
    if (argc >= 2) {
        if (argc > 2) {
            fprintf(stderr, "Unknown argumets will be ignored\n");
        }

        if (!strcmp(argv[1], "--help") || !strcmp(argv[1], "-h")) {
        printf("Usage: ndbs [OPTION]\n"
                "Options:\n"
                "  -h --help        Shows this message\n"
              );
        } else {
            fprintf(stderr, "Unknown option %s\n", argv[1]);
            printf("Usage: ndbs [OPTION]\n"
                    "Options:\n"
                    "  -h --help        Shows this message\n"
                  );
        }
        return 0;
    }

    load_prompt();
    return 0;
}


void help_ndbs()
{
    printf("Usage: COMMAND [OPTION]\n"
            "Commands:\n"
            "  list                 - lists the databases that were created or loaded byndbs\n"
            "  create [FILE NAME]   - creates a new database and expects a filename\n"
            "  load [FILE NAME]     - loads a database named [FILE NAME]\n"
            "  exit                 - exits from ndbs\n"
            "  help                 - shows a this message.\n"
            );
}

void list_database()
{
    return;
}

void print_command_prompt(char const *command)
{
    char c;
    while ((c = getchar()) == '\n')
        printf("%s> ", command);
    ungetc(c, stdin);
}

void insert_record(Table *table)
{
    print_command_prompt("ndbs~create~insert");
    char line[80];
    scanf("%[^\n]", line);

    char name[34];
    char phone[12];
    char email[34];
    sscanf(line, "%s %s %s", name, phone, email);
    strcpy(table->records[table->no_of_records].name, name); 
    strcpy(table->records[table->no_of_records].phone, phone); 
    strcpy(table->records[table->no_of_records].email, email); 
    ++table->no_of_records;
}

void help_create()
{
    printf("Under construction\n");
}

void create_database()
{
    print_command_prompt("ndbs~create~filename");

    char file_name[20];
    scanf("%s", file_name);
    
    print_command_prompt("ndbs~create~subcommands");
    char command[7];
    scanf("%s", command);
    
    Table table;
    table.no_of_records = 0;
    while (true) {

        if (equal(command, Commands[LIST])) {
            if (table.no_of_records) {
                for (uint32_t i = 0; i < table.no_of_records; ++i) {
                    printf("[%s | %s | %s]\n", table.records[i].name, table.records[i].phone, table.records[i].email);
                }
            }
        } else if (equal(command, Commands[INSERT])) {
            insert_record(&table);
        } else if (equal(command, Commands[EXIT])) {
            getchar();
            return;
        } else if (equal(command, Commands[HELP])) {
            /* getchar(); */
            help_create();
        } else if (equal(command, Commands[EXIT]) || equal(command, Commands[FINISH])) {
            getchar();
            return;
        } else {
            getchar();
            command_error(command, help_create);
            return;
        }
        print_command_prompt("ndbs~create~subcommands");
        scanf("%s", command);
    }
    
    // TODO: write data to file
    return;
}

void command_error(char const *command, void(*help) (void))
{
    printf("Unknown command \'%s\'\n", command);
    help();
    return;
}

void load_database()
{
    return;
}
