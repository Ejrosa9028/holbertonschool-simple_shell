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

	if (bytes_read == -1)  /* Si hubo un error al leer */
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

		if (execvp(command, args) == -1)  /* Intentar ejecutar el comando */
		{
			perror("Error al ejecutar el comando");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)  /* Error en el fork */
	{
		perror("Error al crear el proceso hijo");
	}
	else  /* En el padre */
	{
		wait(NULL);  /* Esperar a que el hijo termine */
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

int is_empty_or_spaces(char *str)
{
	int i = 0;

	if (str == NULL)
		return (1);

	for (; str[i]; i++)
	{
		if (str[i] != ' ' && str[i] != '\t')  /* Si hay algo que no es espacio */
			return (0);
	}
	return (1);  /* La cadena está vacía o solo tiene espacios */
}

int is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f');
}

char *trim_spaces(char *str)
{
	char *end;

	while (*str && is_whitespace(*str)) 
	{  /*Eliminar los espacios iniciales*/
		str++;
	}

	if (*str == 0)  /*Si la cadena solo tiene espacios, devolver una cadena vacía*/
		return (str);

	end = str + strlen(str) - 1;

	while (is_whitespace(*end))
	{  /*Eliminar los espacios finales*/
		end--;
	}

	*(end + 1) = '\0';  /*Agregar el terminador nulo al final de la cadena*/
	return (str);
}

void normalize_path(char *path)
{
	char *src = path, *dst = path;
	while (*src)
	{
		*dst = *src;
		if (*src == '/' && *(src + 1) == '/')
		{
			while (*(src + 1) == '/')
				src++;  /*Saltar barras consecutivas*/
		}
		src++;
		dst++;
	}
	*dst = '\0';  /*Finaliza la cadena normalizada*/
}
