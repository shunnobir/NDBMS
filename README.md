# NDBMS
 
This is a very simple database management systemn. You can create your own database file, add data to it, search data and can list data from database. It certainly has limitations and some corner cases which are not handled. Full documentation is given at
github.com/Raihan-28011/NDBMS 
## Commands Syntax
---
| Command |   Structure    |            Sub Commands         |
|:-------:|:--------------:|:-------------------------------:|
| create  | *create* [FILE]| *insert, list, save, help, exit*|
| load    | *load* [FILE]  | *add, list, search, help, exit* |
| help    | *help*         |          *no subcommands*       |
| exit    | *exit*         |          *no subcommands*       |


## Commands Usage
---
## 1. Create
**Syntax**: create *filename*

```txt
ndbms> create data.db
Creating 'data.db'...
ndbms~create>
```
### Sub Commands
- **insert**
	- **Syntax**: insert *name*, *phone*, *email*
	```txt
	ndbms~create> insert Fahmid Ahmed, 01234567891, fahmid365@gmail.com
	____________________________________________________________________
	| Entry ID |      Name        |    Phone    |  	   Email    |
	|__________|__________________|_____________|______________________|
	|     1    |   Fahmid Ahmed   | 01234567891 | fahmid365@gmail.com  |
	|__________|__________________|_____________|______________________|
	ndbms~create>
	```
- **list**
	- **Syntax**: *list*
	```txt
	ndbms~create> list
	____________________________________________________________________
	| Entry ID |      Name        |    Phone    |  	   Email    |
	|__________|__________________|_____________|______________________|
	|     1    |   Fahmid Ahmed   | 01234567891 | fahmid365@gmail.com  |
	|__________|__________________|_____________|______________________|
	ndbms~create>
	```
- **save**
	- **Syntax**: *save*
	```txt
	ndbms~create> save
	All data has been successfully saved to file 'text.db'
	Exiting create mode...
	ndbms>
	```
- help
	- **Syntax**: *help*
	```txt
	ndbms~create> help
	usage: ndbms~create> command [ARGUMENTS]...
    commands:
      insert [NAME], [PHONE], [EMAIL]      insert command accepts three comma seperated
                                           arguments (name, phone and email)
      save                                 saves the inserted data into the frovided file with
                                           create command
      list                                 lists the inserted data
      help                                 shows this message
      exit                                 exit from create mode, shows warning if inserted
                                           data was not saved by the user
	ndbms~create>
	```
- exit
	- **Syntax**: *exit*
	```txt
	ndbms~create> exit
	Exiting create mode...
	ndbms>
	```

### 2. load
**Syntax**: load *filename*
```txt
ndbms> load data.db
Loading data.db...
ndbms~load>
```
### Sub Commands
- list
	- **Syntax**: *list*
	```txt
	ndbms~load> list
	_____________________________________________________________________
	| Entry ID |      Name        |    Phone    |  	     Email   |
	|__________|__________________|_____________|_______________________|
	|     1    |   Fahmid Ahmed   | 01234567891 | fahmid365@gmail.com   |
	|__________|__________________|_____________|_______________________|
	|     2    |   Shimul Islam   | 01234567891 | shimulislam@yahoo.com |
	|__________|__________________|_____________|_______________________|
	ndbms~load>
	```
- add
	- **Syntax**: add *name*, *phone*, *email*
	```txt
	ndbms~load> add Saqlain Mustak, 01234556455, saqlainmustak@gmail.com
	________________________________________________________________________
	| Entry ID |      Name        |    Phone    |  	       Email    |
	|__________|__________________|_____________|__________________________|
	|     3    |  Saqlain Mustak  | 01234556455 | saqlainmustak@gmail.com  |
	|__________|__________________|_____________|__________________________|
	ndbms~load>
	```
- search
	- **Syntax**: search *fieldname* *data*
	```txt
	ndbms~load> search ID 3
	________________________________________________________________________
	| Entry ID |      Name        |    Phone    |  	       Email    |
	|__________|__________________|_____________|__________________________|
	|     3    |  Saqlain Mustak  | 01234556455 | saqlainmustak@gmail.com  |
	|__________|__________________|_____________|__________________________|
	ndbms~load>
	```
- help
	- **Syntax**: *help*
	```txt
	ndbms~load> help
	usage: ndbms~load> command [option]...
	command:
	  list                             lists all data from the file provided
					    with load command
	  add [NAME], [PHONE], [EMAIL]     adds new data to the database file
	  search [FIELD] [DATA]            search [DATA] by [FIELD] which are name,
					    phone and email
	  help                             shows this message
	  exit                             exits from load mode
	ndbms~load>
	```
- exit
	- **Syntax**: *exit*
	```txt
	ndbms~load> exit
	All data has been successfully saved to file 'data.db'
	Exiting load mode...
	ndbms>
	```
			
### 3. help
**Syntax**: *help*
```txt
ndbms> help
usage: ndbms> command [FILE]
command:
  create [FILE]        creates a database file named [FILE]
  load [FILE]          loads a database file named [FILE]
  help                 shows this message
  exit                 exits from ndbms
ndbms>
```

### 4. exit
**Syntax**: *exit*
```txt
ndbms> exit
Exiting...
```

# Limitations

- User can create same file twice.
- Name and email has to be between 1 and 39 characters. And phone has to be between 1 and 19 characters.
- Commands have to be between 1 and 6 characters.
- No checks for tabs or multiple spaces. You can make the program misbehave with tabs and multiple spaces.
- 'remove' operation is still not added.
- If user doesn't use the 'save' command, database will not be saved and file will not be created.
- Now, we can only search data by 'ID'. I didn't add search by name, phone or email operations yet.
- some other corner cases were also not handled.

