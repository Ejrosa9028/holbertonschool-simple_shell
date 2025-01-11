#include "main.h"

/**
 * handle_exit - Handles the built-in "exit" command.
 *               Exits the shell when called.
 * @args: Array of arguments passed to the command.
 *
 * Return: None.
 */
void handle_exit(char **args)
{
	if (args == NULL || args[1] != NULL)
	{
		/* If there are any additional arguments, it displays an error */
		fprintf(stderr, "Usage: exit\n");
	}
	else
	{
		/* If there are no arguments, we terminate the shell */
		exit(0);
	}
}

/**
 * handle_env - Prints the current environment variables.
 * Return: Nothing.
 */
void handle_env(void)
{
	int i = 0;

	/* Print each environment variable in the format NAME=VALUE */
	for (; enviroment[i] != NULL; i++)
	{
		printf("%s\n", enviroment[i]);
	}
}
