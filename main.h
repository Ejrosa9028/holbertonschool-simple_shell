#ifndef MAIN
#define MAIN
#define MAX_LEN 1024
#define DELIM " \t\r\n\a"  /*Delimitadores para dividir la entrada*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>

extern char **environ;  /*Declaración externa de la variable environ*/

/*Prototypes*/
char *read_input(void);
char **parse_input(char *line);
char *find_command_in_path(char *command);
void execute_command(char **args);
void handle_exit(char **args);
void handle_env(void);
int is_empty_or_spaces(char *line);

#endif
