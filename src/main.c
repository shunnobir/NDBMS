#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <inttypes.h>
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
void table_write(char const *fname, Table *table);

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

    while (true) {
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
            return;
        } else {
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

void help_insert() {
    printf("Under development\n");
}

void insert_line(char *name, char *phone, char *email)
{
    char c;
    int comma = 0;
    ptrdiff_t namei = 0, phonei = 0, emaili = 0;

    /* name[namei] = '\0'; */
    /* phone[phonei] = '\0'; */
    /* email[emaili] = '\0'; */
    
    while ((c = getchar())) {
        /* printf("%c %s %s %s\n", c, name, phone, email); */
        if (c == '$')
            break;
        if (c == ',') {
            ++comma;
            if ((c = getchar()) == ' ')
                ;
            else
                ungetc(c, stdin);
            continue;
        }

        if (comma < 2 && c == '\n') {
            ungetc(c, stdin);
            fprintf(stderr, "Wrong format inserted\n");
            help_insert();
            return;
        } else if (comma == 2 && c == '\n') {
            ungetc(c, stdin);
            printf("Warning: Format inserted without an ending character '$'\n");
            return;
        }

        if (!comma) {
            name[namei++] = c;
            name[namei] = '\0';
        } else if (comma == 1) {
            phone[phonei++] = c;
            phone[phonei] = '\0';
        } else {
            email[emaili++] = c;
            email[emaili] = '\0';
        }
    }
    
    if (comma < 2) {
        fprintf(stderr, "Expected comma seperated format\n");
        help_insert();
    }
}

void insert_record(Table *table)
{
    print_command_prompt("ndbs~create~insert");

    char name[34] = { "\0" };
    char phone[12] = { "\0" };
    char email[34] = { "\0" };
    insert_line(name, phone, email);

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
    bool flush = false;
    while (true) {

        if (equal(command, Commands[LIST])) {
            if (table.no_of_records) {
                for (uint32_t i = 0; i < table.no_of_records; ++i) {
                    printf("(%s , %s , %s)\n", table.records[i].name, table.records[i].phone, table.records[i].email);
                }
            }
        } else if (equal(command, Commands[INSERT])) {
            insert_record(&table);
        } else if (equal(command, Commands[HELP])) {
            help_create();
        } else if (equal(command, Commands[EXIT])) {
            getchar();
            break;
        } else if(equal(command, Commands[FINISH])) {
            getchar();
            break;
        } else {
            getchar();
            command_error(command, help_create);
            break;
        }
        print_command_prompt("ndbs~create~subcommands");
        scanf("%s", command);
    }
       
    /* if (flush) */
        table_write(file_name, &table); 
    return;
}

void table_write(char const *fname, Table *table)
{
    printf("Writing\n");
    char file_name[70] = { "/home/raihan/repos/studentDB_c/database/" };
    strcat(file_name, fname);
    printf("filename: %s\n", file_name);
    FILE *file = fopen(file_name, "wb");
    if (file) {
        fwrite((void*)(&table->no_of_records), sizeof(uint32_t), 1, file);
        for (uint32_t i = 0; i < table->no_of_records; ++i) {
            fwrite((void*)(&table->records[i]), sizeof(Fields), 1, file);
        } 
        fclose(file);
    } else {
        fprintf(stderr, "Failed to open file\n");
    }
    perror(NULL);
}

void command_error(char const *command, void(*help) (void))
{
    printf("Unknown command \'%s\'\n", command);
    help();
    return;
}

void save_table(char const *name, Table *table)
{
    char file_name[70] = { "/home/raihan/repos/studentDB_c/database/" };
    strcat(file_name, name);
    printf("Filename: %s\n", file_name);

    FILE *file = fopen(file_name, "rb");
    uint32_t no_of_records = 0;
    
    if (file) {
        fread((void*)&no_of_records, sizeof(uint32_t), 1, file);
        table->no_of_records = no_of_records;

        for (uint32_t i = 0; i < no_of_records; ++i)
            fread((void*)(&table->records[i]), sizeof(Fields), 1, file);

        fclose(file);
    } else {
        fprintf(stderr, "Error openning file\n");
    }
    perror(NULL);
}

void help_load()
{
    printf("Under development\n");
}

void load_database()
{
    printf("ndbs~load~filename> ");
    print_command_prompt("ndbs~load~filename");
    char fname[20];
    scanf("%s", fname);
    getchar();
    Table table;
    save_table(fname, &table);

    printf("ndbs~load~subcommands> ");
    print_command_prompt("ndbs~load~subcommands");
    char command[7];
    scanf("%s", command);

    while (true) {
        if (equal(command, Commands[EXIT])) {
            getchar();
            return;
        } else if (equal(command, Commands[CLOSE])) {
            getchar();
            return;
        } else if (equal(command, Commands[LIST])) {
            for (uint32_t i = 0; i < table.no_of_records; ++i)
                    printf("(%s , %s , %s)\n", table.records[i].name, table.records[i].phone, table.records[i].email);
        } else if (equal(command, Commands[HELP])) {
            getchar();
            help_load();
        } else {
            getchar();
            command_error(command, help_load);
            return;
        }
        print_command_prompt("ndbs~load~subcommands");
        scanf("%s", command);
    }
    return;
}
