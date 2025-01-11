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
		perror("Error al asignar memoria");
		exit(EXIT_FAILURE);
	}

	bytes_read = read(STDIN_FILENO, line, MAX_LEN - 1);

	if (bytes_read == -1)
	{
		perror("Error al leer la entrada");
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
 * parse_input - Splits the input string into tokens.
 * @line: The input string to be split.
 *
 * Return: An array of strings (tokens).
 */
char **parse_input(char *line)
{
	int bufsize = 64, position = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;

	if (tokens == NULL)
	{
	perror("Error al asignar memoria para tokens");
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
				perror("Error al realocar memoria para tokens");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, " ");
	}
	tokens[position] = NULL;
	return (tokens);
}
