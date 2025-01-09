#ifdef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.H>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <erno.h>

extern char **environ;

char *find_comand(char *cmd);
void print_env(void);
void display_prompt(void);
char *read_input(void);
char **split_input(char *input);
void execute_command(char **args);

#endif
