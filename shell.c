#include "main.h"

char *read_input(void)
{
	char *line = NULL;
	size_t bufsize = 0;

	if (getline(&line, &bufsize, stdin) == -1)
	{
		if (feof(stdin))
		{
			return (NULL);
		}

		perror("Error");
		exit(EXIT_FAILURE);
	}
	return (line);
}

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

/*Función para verificar si el comando existe en el PATH*/
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

void execute_command(char **args)
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("Error al ejecutar el comando");
		return;
	}

	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
		{
			perror("Error al ejecutar el comando");
		}
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(NULL);
	}
}

/*Función para manejar el comando exit*/
void handle_exit(char **args)
{
	if (args[1] != NULL)
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

/*Función para manejar el comando env (imprime el entorno actual)*/
void handle_env(void)
{
	int i = 0;

	/*Imprimimos cada variable de entorno en formato KEY=VALUE*/
	for (; environ[i] != NULL; i++)
	{
		printf("%s\n", environ[i]);
	}
}
