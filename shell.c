#include "main.h"

/**
 * read_input - Reads the data entered by the user
 *
 * Return: A pointer to the input string or NULL if there is an error.
 */
char *read_input(void)
{
	char *line = NULL;
	size_t bufsize = 0;

	if (getline(&line, &bufsize, stdin) == -1)
	{
		if (line == NULL)
		{
			return (NULL);
		}

		perror("./hsh");
		exit(EXIT_FAILURE);
	}
	return (line);
}

/**
 * parse_input - Splits the input string into tokens
 * @line: The input string to be split
 *
 * Return: An array of strings (tokens).
 */
char **parse_input(char *line)
{
	int bufsize = 64;
	int position = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;

	token = strtok(line, DELIM);
	while (token != NULL)
	{
		tokens[position] = token;
		position++;

		if (position >= bufsize)
		{
			bufsize += 64;
			tokens = realloc(tokens, bufsize * sizeof(char *));
		}

		token = strtok(NULL, DELIM);
	}
	tokens[position] = NULL;
	return (tokens);
}

/**
 * find_command_in_path - Search for a command in the directories listed in PATH.
 *
 * @command: The command to search for..
 *
 * Return: A string containing the full path to the command if found,
 *         or NULL if the command is not found.
 */
char *find_command_in_path(char *command)
{
	char *path = getenv("PATH");  /*We get the PATH environment variable*/
	char *path_copy = strdup(path);  /*We make a copy of PATH*/
	char *dir = strtok(path_copy, ":");  /*We divide the PATH into directories*/
	char *full_path = NULL;

	/*We look for the command in each directory of PATH*/
	while (dir != NULL)
	{
		full_path = malloc(strlen(dir) + strlen(command) + 2);
		sprintf(full_path, "%s/%s", dir, command);

		/*If the file exists and is executable, we return it*/
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}

		free(full_path);  /*We free memory if we don't find it*/
		dir = strtok(NULL, ":");  /*Let's go to the next directory*/
	}

	free(path_copy);
	return (NULL);  /*If we don't find it, we return NULL*/
}

/**
 * execute_command - Execute a command by creating a new process
 * @args: Array of command arguments
 *
 * Return: None.
 */
void execute_command(char **args)
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("./hsh");
		return;
	}

	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
		{
			perror(args[0]);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(NULL);
	}
}

/**
 * handle_exit - Handles the built-in "exit" command.
 *               Exits the shell when called.
 *
 * @args: Array of arguments passed to the command.
 *
 * Return: None.
 */
void handle_exit(char **args)
{
	if (args == NULL || args[1] != NULL)
	{
		/*If there are any additional arguments, it displays an error*/
		fprintf(stderr, "Usage: exit\n");
	}
	else
	{
		/*If there are no arguments, we terminate the shell*/
		exit(0);
	}
}
