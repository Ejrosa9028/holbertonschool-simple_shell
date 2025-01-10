#include "main.h"

/**
 * main - Entry point for the shell program
 *
 * Return: Always 0.
 */
int main(void)
{
	char *line, **args;

	do {
		if (isatty(STDIN_FILENO)) /*Dispaly prompt in interactive mode*/
		{
			printf("($) ");
		}

		line = read_input(); /*Read user input*/

		if (line == NULL) /*If (Ctrl+D), exit the shell*/
		{
			printf("\n");
			break;
		}

		args = parse_input(line); /*Process input*/

		if (args[0] != NULL && strcmp(args[0], "exit") == 0) /*If "exit, exit*/
		{
			handle_exit(args);
			free(line);
			free(args);
			break; /*Exit the loop and terminate shell*/
		}

		if (args[0] != NULL && strcmp(args[0], "env") == 0) /*If "env", show env*/
		{
			handle_env();
			free(line);
			free(args);
			continue;  /*Re-show prompt*/
		}

		execute_command(args); /*Execute command*/
		free(line); /*Free line memory*/
		free(args); /*Free args memory*/
	} while (1);

	return (0);
}
