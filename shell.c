#include "main.h"

/**
 * read_input - Lee los datos introducidos por el usuario
 *
 * Return: Un puntero a la cadena de entrada o NULL si hay un error.
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
 * parse_input - Divide la cadena de entrada en tokens
 * @line: El string de entrada que se va a dividir
 *
 * Return: Un array de strings (tokens).
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
 * find_command_in_path - Busca un comando en los directorios listados en PATH.
 *
 * @command: El comando a buscar.
 *
 * Return: Una cadena que contiene la ruta completa al comando si se encuentra,
 *         o NULL si no se encuentra el comando.
 */
char *find_command_in_path(char *command)
{
	char *path = getenv("PATH");  /*Obtenemos la variable de entorno PATH*/
	char *path_copy = strdup(path);  /*Hacemos una copia de PATH*/
	char *dir = strtok(path_copy, ":");  /*Dividimos el PATH en directorios*/
	char *full_path = NULL;

	/*Buscamos el comando en cada directorio de PATH*/
	while (dir != NULL)
	{
		full_path = malloc(strlen(dir) + strlen(command) + 2);
		sprintf(full_path, "%s/%s", dir, command);

		/*Si el archivo existe y es ejecutable, lo devolvemos*/
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}

		free(full_path);  /*Liberamos memoria si no lo encontramos*/
		dir = strtok(NULL, ":");  /*Vamos al siguiente directorio*/
	}

	free(path_copy);
	return (NULL);  /*Si no lo encontramos, devolvemos NULL*/
}

/**
 * execute_command - Ejecuta un comando creando un nuevo proceso
 * @args: Array de argumentos de comandos
 *
 * Return: Nada.
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
 * handle_exit - Maneja el comando incorporado "exit".
 *               Sale del shell cuando se le llama.
 *
 * @args: Array de argumentos pasados al comando.
 *
 * Return: None.
 */
void handle_exit(char **args)
{
	if (args == NULL || args[1] != NULL)
	{
		/*Si hay algún argumento adicional, muestra un error*/
		fprintf(stderr, "Usage: exit\n");
	}
	else
	{
		/*Si no hay argumentos, terminamos el shell*/
		exit(0);
	}
}
