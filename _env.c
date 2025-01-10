#include "main.h"

/**
 * handle_env - Prints the current environment variables.
 *
 * This function prints the environment variables currently set in the system.
 * It prints each variable in the format: NAME=VALUE
 *
 * Return: Nothing.
 */
void handle_env(void)
{
	int i = 0;

	/* Print each environment variable in the format NAME=VALUE */
	for (; environ[i] != NULL; i++)
	{
		printf("%s\n", environ[i]);
	}
}
