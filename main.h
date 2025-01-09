#ifndef MAIN
#define MAIN

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

extern char **environ;  /*Declaración externa de la variable environ*/

/*Prototipo*/
char *read_input(void);
char **parse_input(char *line);
char *find_command_in_path(char *command);
void execute_command(char **args);
void handle_exit(char **args);
void handle_env(void);

#endif
