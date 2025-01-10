#include "main.h"

/**
 * read_input - Reads the data entered by the user
 *
 * Return: A pointer to the input string or NULL if there is an error.
 */
char *read_input(void)
{
	char *line = malloc(MAX_LEN * sizeof(char));
	ssize_t bytes_read;

	if (line == NULL)
	{
		perror("Error allocating memory");
		exit(EXIT_FAILURE);
	}

	bytes_read = read(STDIN_FILENO, line, MAX_LEN - 1);

	if (bytes_read == -1)
	{
		perror("Error reading input");
		free(line);
		return (NULL);
	}

	if (bytes_read == 0)
	{
		free(line);
		return (NULL);
	}

	line[bytes_read] = '\0';

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

	if (tokens == NULL)
	{
		perror("Error allocating memory for tokens");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, " ");
	while (token != NULL)
	{
		tokens[position] = token;
		position++;

		if (position >= bufsize)
		{
			bufsize += 64;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (tokens == NULL)
			{
				perror("Error reallocating memory for tokens");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, " ");
	}
	tokens[position] = NULL;
	return (tokens);
}

/**
 * find_command_in_path - Searches for a command in directories listed in PATH
 * @command: The command to search for
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

	printf("PATH: %s\n", path);

	while (dir != NULL)
	{
		full_path = malloc(strlen(dir) + strlen(command) + 2);
		sprintf(full_path, "%s/%s", dir, command);

		if (access(full_path, X_OK) == 0)
		{
			printf("Found command: %s\n", full_path);
			free(path_copy);
			return (full_path);
		}

		free(full_path);
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	printf("Command not found: %s\n", command);
	return (NULL);
}

/**
 * execute_command - Executes a command by creating a new process
 * @args: Array of command arguments
 *
 * Return: None.
 */
void execute_command(char **args)
{
	pid_t pid = fork();

	if (pid == 0)
	{
		char *full_path = find_command_in_path(args[0]);

		if (full_path)
		{
			execvp(full_path, args);
			perror("Error executing command");
			free(full_path);
		}
		else
		{
			fprintf(stderr, "Command not found: %s\n", args[0]);
		}
		exit(EXIT_FAILURE);
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

/**
 * handle_exit - Handles the built-in "exit" command
 * @args: Array of arguments passed to the command
 *
 * Return: None.
 */
void handle_exit(char **args)
{
	if (args == NULL || args[1] != NULL)
	{
		fprintf(stderr, "Usage: exit\n");
	}
	else
	{
		exit(0);
	}
}

/**
 * handle_env - Prints the current environment variables
 *
 * Return: Nothing.
 */
void handle_env(void)
{
	int i = 0;

	for (; environ[i] != NULL; i++)
	{
		printf("%s\n", environ[i]);
	}
}

/**
 * is_empty_or_spaces - Checks if a string is empty or contains only spaces
 * @str: The string to check
 *
 * Return: 1 if the string is empty or contains only spaces, 0 otherwise.
 */
int is_empty_or_spaces(char *str)
{
	int i = 0;

	if (str == NULL)
		return (1);

	for (; str[i]; i++)
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
	}
	return (1);
}

/**
 * is_whitespace - Checks if a character is a whitespace character
 * @c: The character to check
 *
 * Return: 1 if the character is a whitespace character, 0 otherwise.
 */
int is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' ||
			c == '\r' || c == '\v' || c == '\f');
}

/**
 * trim_spaces - Trims leading and trailing whitespace from a string
 * @str: The string to trim
 *
 * Return: A pointer to the trimmed string.
 */
char *trim_spaces(char *str)
{
	char *end;

	while (*str && is_whitespace(*str))
	{
		str++;
	}

	if (*str == 0)
		return (str);

	end = str + strlen(str) - 1;

	while (is_whitespace(*end))
	{
		end--;
	}

	*(end + 1) = '\0';
	return (str);
}

/**
 * normalize_path - Normalizes a file path by removing consecutive slashes
 * @path: The path to normalize
 *
 * Return: None.
 */
void normalize_path(char *path)
{
	char *src = path, *dst = path;

	while (*src)
	{
		*dst = *src;
		if (*src == '/' && *(src + 1) == '/')
		{
			while (*(src + 1) == '/')
				src++;
		}
		src++;
		dst++;
	}
	*dst = '\0';
}

/**
 * main - Entry point of the shell program
 *
 * Return: 0 on success, otherwise a different number.
 */
int main(void)
{
	char *input;
	char **args;

	while (1)
	{
		printf("$ ");
		input = read_input();
		if (input == NULL)
			continue;
		args = parse_input(input);
		if (args[0] == NULL)
		{
			free(input);
			free(args);
			continue;
		}
		if (strcmp(args[0], "exit") == 0)
			handle_exit(args);
		else if (strcmp(args[0], "env") == 0)
			handle_env();
		else
			execute_command(args);

		free(input);
		free(args);
	}

	return (0);
}
