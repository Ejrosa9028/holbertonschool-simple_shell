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
	char *path_copy, *dir, *full_path;

	if (path == NULL)
		return (NULL);

	path_copy = strdup(path); /*Make a copy of PATH*/
	if (path_copy == NULL)
	{
		perror("Error duplicating PATH");
			return (NULL);
	}

	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		full_path = malloc(strlen(dir) + strlen(command) + 2);
		if (full_path == NULL)
		{
			perror("Error allocating memory for command path");
			free(path_copy);
			return (NULL);
		}

		sprintf(full_path, "%s/%s", dir, command);

		/*Check if the file exists and is executable */
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}

		free(full_path);
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
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
				char *temp = malloc(strlen("/bin/") + strlen(command) + 1);
				if (temp == NULL)
				{
					perror("Error allocating memory for command path");
					exit(EXIT_FAILURE);
				}
				strcpy(temp, "/bin/");
				strcat(temp, args[0]);
				command = temp;
			}
		}
		if (execvp(command, args) == -1)
		{
			perror("Error executing command");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
	{
		perror("Error creating child process");
	}
	else
	{
		wait(NULL);
	}
}
