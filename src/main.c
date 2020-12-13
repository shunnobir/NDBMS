#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

typedef enum {
    CREATE_COMMAND  , LOAD_COMMAND      ,
    EXIT_COMMAND    , INSERT_COMMAND    ,
    LIST_COMMAND    , HELP_COMMAND      ,
    SAVE_COMMAND    , ADD_COMMAND       ,
    SEARCH_COMMAND  , INITIAL_COMMAND   ,
    UNKNOWN_COMMAND , WRONG_FORMAT      ,
} CommandType;

#define HANDLED_BY_UNRECOGNIZED_COMMAND_FUNCTION

char const Commands[][7] = {
    "create", "load"    ,
    "exit"  , "insert"  ,
    "list"  , "help"    ,
    "save"  , "add"     ,
    "search"
};

typedef void Func_t(void);
typedef struct Database Database;
typedef struct Fields Record;

struct Fields {
    char name[40];
    char phone[20];
    char email[40];
};

struct Database {
    uint32_t no_of_records;
    Record records[20];
};

/*  Utility Functions */
void command_prompt(char const *prompt);
CommandType get_command(CommandType commandType);
CommandType initial_command(void);
CommandType check_command(char const *command, Func_t func);
bool equal(char const *str1, char const *str2);
bool valid_char(char *c);
void unrecognized_command(char const *command, Func_t *func);
void wrong_format(Func_t *func);
void get_filename(char *fname);
char scan_command(char *command);
bool check_wrong_format(char *c);

/* Interface functions */
void database_insert(Database *database, Func_t *func);
void database_help(void);
void database_exit(void);
void database_print_record(uint32_t ID, Record *record);

/* functions for Create command */
CommandType create_command(void);
void database_create(void);
void database_create_insert(Database *database);
void database_create_list_inserted_data(Database *database);
void database_create_help(void);
void database_create_write_database(Database *database, char const *fname);
void database_create_exit(Database *database);

/* Functions for Load Command */
CommandType load_command(void);
void database_load(void);
bool database_load_read_datafile(Database *database, char const *fname);
void database_load_list_data(Database *database);
void database_load_add_data(Database *database);
void database_load_search_data(Database *database);
void database_load_exit(void);
void database_load_save_data(Database *database, char const *fname);
void database_load_help(void);

int main(void)
{
    CommandType commandType;
    
    while (true) {
        command_prompt("dbs");
        commandType = get_command(INITIAL_COMMAND);
        switch (commandType) {
            case CREATE_COMMAND:
                database_create();
                break;
            case LOAD_COMMAND:
                database_load();
                break;
            case HELP_COMMAND:
                database_help();
                break;
            case WRONG_FORMAT:
                wrong_format(database_help);
                database_exit();
                return EXIT_FAILURE;
            case EXIT_COMMAND:
                database_exit();
                return EXIT_SUCCESS;
            default:
                HANDLED_BY_UNRECOGNIZED_COMMAND_FUNCTION;
        }
    }
}

void command_prompt(char const *prompt)
{
    printf("%s> ", prompt); 
}

CommandType get_command(CommandType commandType)
{
#define IGNORE
    switch (commandType) {
    case CREATE_COMMAND:
        return create_command();
    case INITIAL_COMMAND:
        return initial_command();
    case LIST_COMMAND:
        return LIST_COMMAND;
    case LOAD_COMMAND:
        return load_command();
    default:
        IGNORE;
    } 

    return UNKNOWN_COMMAND;
}

CommandType initial_command()
{
    char c;
    char command[7];
    uint8_t length =7, index = 0;
    while (valid_char(&c) && --length)
        command[index++] = c;
    command[index] = '\0'; 
    CommandType returned_value = check_command(command, database_help);

    if (returned_value == CREATE_COMMAND || returned_value == LOAD_COMMAND) {
        char temp;
        if (c == '\n') 
            return WRONG_FORMAT;
        else if (c == ' ' && (temp = getchar())  == '\n')
            return WRONG_FORMAT;
        else if (c == ' ' && temp != '\n')
            ungetc(temp, stdin);
    }
    return returned_value;
}

CommandType check_command(char const *command, Func_t func)
{
    if (equal(command, Commands[CREATE_COMMAND]))
        return CREATE_COMMAND;
    else if (equal(command, Commands[EXIT_COMMAND]))
        return EXIT_COMMAND;
    else if (equal(command, Commands[LOAD_COMMAND]))
        return LOAD_COMMAND;
    else if (equal(command, Commands[INSERT_COMMAND]))
        return INSERT_COMMAND;
    else if (equal(command, Commands[LIST_COMMAND]))
        return LIST_COMMAND;
    else if (equal(command, Commands[ADD_COMMAND]))
        return ADD_COMMAND;
    else if (equal(command, Commands[SEARCH_COMMAND]))
        return SEARCH_COMMAND;
    else if  (equal(command, Commands[SAVE_COMMAND]))
        return SAVE_COMMAND;
    else if (equal(command, Commands[HELP_COMMAND]))
        return HELP_COMMAND;
    else {
        unrecognized_command(command, func);
        return UNKNOWN_COMMAND;
    }
}

bool equal(char const *str1, char const *str2)
{
    return strcmp(str1, str2) == 0;
}

bool valid_char(char *c)
{
    return (((*c = getchar()) != '\n') && (*c != ' '));
}

void unrecognized_command(char const *command, Func_t *func)
{
    fprintf(stderr, "Unrecognized command '%s'\n", command);
    func();
}

void wrong_format(Func_t *func)
{
    fprintf(stderr, "syntax error [wrong formatted command]\n");
    func();
}

void get_filename(char *fname)
{
    char c;
    uint8_t length = 20, index = 0;

    while (valid_char(&c) && --length)
        fname[index++] = c;
    fname[index] = '\0';
}

char scan_command(char *command)
{
    char c;
    uint8_t length = 7, index = 0;
    while (valid_char(&c) && --length)
       command[index++] = c;
    command[index] = '\0';
    return c;
}

bool check_wrong_format(char *c)
{
    char temp;
    if (*c == '\n') 
        return true;
    else if (*c == ' ' && (temp = getchar())  == '\n')
        return true;
    else if (*c == ' ' && temp != '\n')
        ungetc(temp, stdin);
    return false;
}

/* Interface Functions */
void database_insert(Database *database, Func_t *func)
{
#define eat_newline getchar
    char line[120];
    scanf(" %[^\n]", line); 
    eat_newline();

    char name[40], phone[20], email[40];
    size_t retad_char = sscanf(line, "%[^,], %[^,], %[^\n]", name, phone, email);
    
    if (retad_char != 3)
        wrong_format(func);
    
    strcpy(database->records[database->no_of_records].name, name);
    strcpy(database->records[database->no_of_records].phone, phone);
    strcpy(database->records[database->no_of_records].email, email);
    ++database->no_of_records;
    database_print_record(database->no_of_records, &database->records[database->no_of_records-1]);
}

void database_help()
{
    printf("usage: dbs> command [FILE]\n"
            "command:\n"
            "  create [FILE]        creates a database file named [FILE]\n"
            "  load [FILE]          loads a database file named [FILE]\n"
            "  help                 shows this message\n"
            "  exit                 exits from dbs\n"
          );
}

void database_exit()
{
    printf("Exiting...\n");
}

void database_print_record(uint32_t ID, Record *record)
{
    printf("Entry ID: %u\n"
            "Name: %s\n"
            "Phone: %s\n"
            "Email: %s\n",
            ID,
            record->name,
            record->phone,
            record->email);
}

/* Command: Create */
CommandType create_command()
{
    char command[7];
    char c = scan_command(command);

    CommandType returned_value = check_command(command, database_create_help);
    if (returned_value == INSERT_COMMAND && check_wrong_format(&c))
            return WRONG_FORMAT;
    return returned_value;
}

void database_create()
{
#define RETURN_TO_MAIN return;
    
    char fname[20];
    get_filename(fname);
    printf("Creating '%s'...\n", fname);

    Database database = { .no_of_records = 0 };
    CommandType commandType;
    while (true) {
        command_prompt("dbs~create");
        commandType = get_command(CREATE_COMMAND);
        switch (commandType) {
            case INSERT_COMMAND:
                database_create_insert(&database);
                break;
            case LIST_COMMAND:
                database_create_list_inserted_data(&database);
                break;
            case SAVE_COMMAND:
                database_create_write_database(&database, fname);
                printf("Exiting create mode...\n");
                RETURN_TO_MAIN;
            case HELP_COMMAND:
                database_create_help();
                break;
            case EXIT_COMMAND:
                database_create_exit(&database);
                RETURN_TO_MAIN;
            case WRONG_FORMAT:
                wrong_format(database_create_help);
                RETURN_TO_MAIN;
            default:
                HANDLED_BY_UNRECOGNIZED_COMMAND_FUNCTION;
        }
    }
}

void database_create_insert(Database *database)
{
    database_insert(database, database_create_help);
}

void database_create_list_inserted_data(Database *database)
{
    uint32_t dataSize = database->no_of_records;
    for (uint32_t id = 0; id < dataSize; ++id) {
        database_print_record(id+1, &database->records[id]);
        putchar('\n');
    }
}

void database_create_help()
{
    printf("usage: dbs~create> command [ARGUMENTS]...\n"
            "commands:\n"
            "  insert [NAME], [PHONE], [EMAIL]      insert command accepts three comma seperated\n"
            "                                       arguments (name, phone and email)\n"
            "  save                                 saves the inserted data into the frovided file with\n"
            "                                       create command\n"
            "  list                                 lists the inserted data\n"
            "  help                                 shows this message\n"
            "  exit                                 exit from create mode, shows warning if inserted\n"
            "                                       data was not saved by the user\n"
          );

}

void database_create_write_database(Database *database, char const *fname)
{
    FILE *datafile = fopen(fname, "wb");
    if (datafile) {
        uint32_t dataSize = database->no_of_records;
        fwrite(&dataSize, sizeof(uint32_t), 1, datafile);
        for (uint32_t i = 0; i < dataSize; ++i) {
            fwrite(&database->records[i], sizeof(Record), 1, datafile);
        }
    } else {
        fprintf(stderr, "Error creating '%s'\n", fname);
        return;
    }
    printf("All data has been successfully saved to file '%s'\n",  fname);
}

void database_create_exit(Database *database)
{
    if (database->no_of_records)
        printf("Exit without saving data\n");
    printf("Exiting create mode...\n");
}


/* Command: Load */
CommandType load_command()
{
    char command[7];
    char c = scan_command(command);
    
    CommandType returned_value = check_command(command, database_load_help);
    if ((returned_value == ADD_COMMAND || returned_value == SEARCH_COMMAND)
            && check_wrong_format(&c))
        return WRONG_FORMAT;
    return returned_value;
}

void database_load()
{
    char fname[20];
    get_filename(fname);
    printf("Loading '%s'...\n", fname);

    Database database;
    bool returned_value = database_load_read_datafile(&database, fname);
    if (!returned_value)
        return;

    while (true) {
        command_prompt("dbs~load");
        CommandType commandType = get_command(LOAD_COMMAND);

        switch (commandType) {
        case LIST_COMMAND:
            database_load_list_data(&database);
            break;
        case ADD_COMMAND:
            database_load_add_data(&database);
            break;
        case SEARCH_COMMAND:
            database_load_search_data(&database);
            break;
        case HELP_COMMAND:
            database_load_help();
            break;
        case WRONG_FORMAT:
            wrong_format(database_load_help);
            break;
        case EXIT_COMMAND:
            database_load_save_data(&database, fname);
            database_load_exit();
            RETURN_TO_MAIN;
        default:
            ;
        }
    }
}

bool database_load_read_datafile(Database *database, char const *fname)
{
    FILE *file = fopen(fname, "rb");
    if (file) {
        uint32_t no_of_records = 0;
        fread(&no_of_records, sizeof(uint32_t), 1, file);
        database->no_of_records = no_of_records;

        for (uint32_t id = 0; id < no_of_records; ++id)
            fread(&database->records[id], sizeof(Record), 1, file);
        return true;
    } else
        fprintf(stderr, "Error opening file\n");
    return false;
}

void database_load_save_data(Database *database, char const *fname)
{
    database_create_write_database(database, fname);
}

void database_load_exit()
{
    printf("Exiting load mode...\n");
}

void database_load_search_data(Database *database)
{
#define eat_newline getchar
    char command[7];
    scanf(" %s ", command);

    /* assuming you entered ID */
    uint32_t ID = 0;
    scanf("%u", &ID);
    eat_newline();

    printf("Search result:\n");
    database_print_record(ID, &database->records[ID-1]);
}

void database_load_add_data(Database *database)
{
    database_insert(database, database_load_help);
}

void database_load_help()
{
    printf("usage: dbs~load> command [option]...\n"
            "command:\n"
            "  list                             lists all data from the file provided\n"
            "                                   with load command\n"
            "  add [NAME], [PHONE], [EMAIL]     adds new data to the database file\n"
            "  search [FIELD] [DATA]            search [DATA] by [FIELD] which are name,\n"
            "                                   phone and email\n"
            "  help                             shows this message\n"
            "  exit                             exits from load mode\n"
          );
}

void database_load_list_data(Database *database) 
{
    database_create_list_inserted_data(database); /* reusing same functions rather implemnting them again */
}
