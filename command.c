#include "main.h"

/**
 * find_command_in_path - Search for a command in
 * the directories listed in PATH.
 * @command: The command to search for.
 *
 * Return: A string containing the full path to the command if found,
 *         or NULL if the command is not found.
 */
char *find_command_in_path(char *command)
{
	char *path = getenv("PATH");
	char *path_copy = strdup(path);
	char *dir = strtok(path_copy, ":");
	char *full_path = NULL;

	while (dir != NULL)
	{
		full_path = malloc(strlen(dir) + strlen(command) + 2);
		sprint(full_path, "%s/%s", dir, command);

		/* If the file exists and is executable, we return it */
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}
	}
	free(full_path);
	dir = strtok(NULL, ":");
}

/**
 * execute_command - Execute a command by creating a new process.
 * @args: Array of command arguments.
 *
 * Return: None.
 */
void execute_command(char **args)
{
	pid_t pid = fork();

	if (pid == 0)
	{
		char *command = args[0];

		/* Normalizamos la ruta del comando antes de ejecutar */
		normalize_path(command);

		/* Comprobar si el PATH está vacío, si lo está usar la ruta completa */
		if (getenv("PATH") == NULL || strlen(getenv("PATH")) == 0)
		{
			if (command[0] != '/')
			{
				command = malloc(strlen("/bin/") + strlen(command) + 1);
				strcpy(command, "/bin/");
				strcat(command, args[0]);
			}
		}
		if (execvp(command, args) == -1) /*intentar ejecutar el comando*/
		{
			perror("Error al ejecutar el comando");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
	{
		perror("Error al crear el proceso hijo");
	}
	else
	{
		wait(NULL);
	}
}
