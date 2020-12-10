#include <stdio.h>
#include <assert.h>
#include <stddef.h>
#include <stdbool.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


/* Declaring command enums */
enum commands {             /*  Values */
    LIST    ,   CREATE  ,   /* 0 , 1 , */
    INSERT  ,   FINISH  ,   /* 2 , 3 , */ 
    LOAD    ,   ADD     ,   /* 4 , 5 , */
    GET     ,   CLOSE   ,   /* 6 , 7 , */
    SHOW    ,   HELP    ,   /* 8 , 9 , */
    EXIT                    /* 10      */
};

/* These are the commands that will be used in the system as commands and subcommands */
char const *Commands[] = { 
    "list"  ,   "create",   /* Commands[LIST]   , Commands[CREATE], */
    "insert",   "finish",   /* Commands[INSERT] , Commands[FINISH], */
    "load"  ,   "add"   ,   /* Commands[LOAD]   , Commands[ADD]   , */
    "get"   ,   "close" ,   /* Commands[GET]    , Commands[CLOSE] , */
    "show"  ,   "help"  ,   /* Commands[SHOW]   , Commands[HELP]  , */
    "exit"                  /* Commands[EXIT]   ,                   */
};


/* These are the fields of the database */
typedef struct Fields {
    char name[34];
    char phone[12];
    char email[34];
} Fields;

/* This is the Table which contains the data */
typedef struct table {
    uint32_t no_of_records; /* This will store the number of total records that has been entered */
    Fields records[20];
} Table;


/* Function type */
typedef void Func_t (void);

/* Typedef to declare index type for arrays */
typedef uint32_t Index_t;

/* Typedef for counter type */
typedef uint32_t Counter;

/* To avoid null statement */
#define IGNORE


/*           Function declarations 
 + -----------------         ----------------+ */

/* Functions for 'list' commands */
void list_database();
void save_file_names(char const *fname);


/* Functions for 'create' command */
void create_database(void);
void create_insert_record();


/* Functons for 'load' command */
void load_database();
void add_record();
void get_record();
void show_all_records();
void close_database();


/* Fnctions for handling command errors and to print out help */
void help_ndbs(int argc, char const *argv);
void help_ndbs_commands();
void help_list_command();
void help_create_command();
void help_load_command();


/* This function takes the unrecognized command name and the appropriate help function pointer */ 
void command_error(char const *command, Func_t *func);


void table_write(char const *fname, Table *table);


/*Utility functions */
void print_ndbs_prompt(); /* prints the main prompt */
void print_command_prompt(char const *command); /* Prints the prompt till user enters newline */
void get_command(char *command, uint8_t length); /* gets the command from user and stores it in 'command' */
bool equal(char const *str1, char const *str2);  /* compares two strings */


/* Function that executes operations according to the commands provided by user */
void load_prompt()
{
    print_ndbs_prompt();
    print_command_prompt("ndbs");

    /* As no command is greater than length of 6, we set the size to 7 */
    char command[7];
    get_command(command, 7);

    /* while user doesn't want to exit or enters unrecognized command */
    while (true) {
        if (equal(command, Commands[LIST])) {
            list_database();
        } else if (equal(command, Commands[CREATE])) {
            create_database();
        } else if (equal(command, Commands[LOAD])) {
            load_database();
        } else if (equal(command, Commands[HELP])) {
            help_ndbs_commands();
        } else if (equal(command, Commands[EXIT])){
            return;
        } else {
            command_error(command, help_ndbs_commands);
            return;
        }

        print_ndbs_prompt();
        print_command_prompt("ndbs");
        get_command(command, 7);
    }
}

/*          Main Function
 +---------------      --------------+ */

int main(int argc, char *argv[static 1]) {
    static_assert(sizeof(Fields) == 80, "Nope");
    /* If user wants to know about the application itself */
    if (argc >= 2) {
        help_ndbs(argc, argv[1]);
        return 0;
    }

    load_prompt();
    return 0;
}


/*          Functions definitions 
 +----------------         ---------------+ */

void print_ndbs_prompt()
{
    printf("ndbs> ");
}

void print_command_prompt(char const *command)
{
    char c;
    while ((c = getchar()) == '\n')
        printf("%s> ", command);
    ungetc(c, stdin);
}

void get_command(char *command, uint8_t length)
{
    char c;
    uint8_t i = 0;
    while ((c = getchar()) != '\n' && c != ' ' && --length)
        command[i++] = c;
    command[i] = '\0';
}

bool equal(char const *str1, char const *str2)
{
    return strcmp(str1, str2) == 0;
}

void help_ndbs(int argc, char const *argv_1)
{
    char const help_msg[] = { "Usage: ndbs [OPTION]\n"
                              "Options:\n"
                              "  -h --help        Shows this message\n"
                            };

    if (argc > 2)    /* If the user enters unrecognized options */
        fprintf(stderr, "Warning: Unknown argumets will be ignored\n");

    if (equal(argv_1, "--help") || equal(argv_1, "-h")) {
        printf("%s", help_msg);
    } else {
        fprintf(stderr, "Wrong option '%s'\n", argv_1);
        printf("%s", help_msg);
    }

}

void help_ndbs_commands()
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


void help_insert() {
    printf("Under development\n");
}

void insert_get_line(char *name, char *phone, char *email)
{
    /* We expect input in comma separeted format.
      Like this "name, phone_no, email"        */
    
    char c;
    Counter comma = 0;
    Index_t name_i = 0, phone_i = 0, email_i = 0;

    while ((c = getchar())) {
        if (c == ',') {
            ++comma;
           
            /* Checks if the input is of "---, --" or "---,--" format. '-' is any char */
            if ((c = getchar()) == ' ')
                IGNORE;  /* This is a null statement in disguise */
            else
                ungetc(c, stdin);

            continue;
        }

        /* temporary code block to make temp varibale's scope small */
        {
            char temp;
            
            /* checks if format is "--- ," or not */
            if (c == ' ' && (temp = getchar()) == ',') {
                ungetc(temp, stdin);
                continue;
            } else if (c == ' ' && temp != ',')
                ungetc(temp, stdin);
        }
        /* scope ends */

        if (comma < 2 && c == '\n') {  /* if comma count is not equals to 2 but user has entered newline */
            ungetc(c, stdin);
            fprintf(stderr, "Wrong format inserted\n");
            help_insert();
            return;
        } else if (comma == 2 && c == '\n') {  /* if count is 2 and we encounter newline that means end of input */
            ungetc(c, stdin);
            return;
        }

        if (!comma && name_i <= 33) {  /* when comma count is 0, name is expected */
            name[name_i++] = c;
            name[name_i] = '\0';
        } else if (comma == 1 && phone_i <= 33) {  /* count=1, phone_no is expected */
            phone[phone_i++] = c;
            phone[phone_i] = '\0';
        } else if (comma == 2 && email_i <= 33) {  /* count=2, email is expected */
            email[email_i++] = c;
            email[email_i] = '\0';
        }
    }
    
    if (comma < 2) { /* Less than 2 comma means invalid format */
        fprintf(stderr, "Expected comma seperated format\n");
        help_insert();
    }
}

void create_insert_record(Table *table)
{
    print_command_prompt("ndbs~create~insert");

    char name[34] = { "\0" };
    char phone[12] = { "\0" };
    char email[34] = { "\0" };
    insert_get_line(name, phone, email);

    strcpy(table->records[table->no_of_records].name, name); 
    strcpy(table->records[table->no_of_records].phone, phone); 
    strcpy(table->records[table->no_of_records].email, email); 
    ++table->no_of_records;
}

void help_create_command()
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
            create_insert_record(&table);
        } else if (equal(command, Commands[HELP])) {
            help_create_command();
        } else if (equal(command, Commands[EXIT])) {
            getchar();
            break;
        } else if(equal(command, Commands[FINISH])) {
            getchar();
            break;
        } else {
            getchar();
            command_error(command, help_create_command);
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

void help_load_command()
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
            help_load_command();
        } else {
            getchar();
            command_error(command, help_load_command);
            return;
        }
        print_command_prompt("ndbs~load~subcommands");
        scanf("%s", command);
    }
    return;
}
