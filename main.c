#include "main.h"

int main(void)
{
	char *line;
	char **args;

	do {
		/*Muestra el prompt solo en modo interactivo*/
		if (isatty(STDIN_FILENO))
		{
			printf("($) ");
		}

		line = read_input(); /*Lee la entrada del usuario*/

		/*Si hemos llegado al EOF (Ctrl+D), terminamos el shell*/
		if (line == NULL)
		{
			printf("\n");
			break;
		}

		args = parse_input(line); /*Procesa la entrada*/

		/*Si el comando es "exit", salimos de shell*/
		if (args[0] != NULL && strcmp(args[0], "exit") == 0)
		{
			handle_exit(args);
			free(line);
			free(args);
			break; /*Salimos del bucle y terminamos shell*/
		}

		/*Si el comando es "env", mostramos el entorno*/
		if (args[0] != NULL && strcmp(args[0], "env") == 0)
		{
			handle_env();
			free(line);
			free(args);
			continue;  
			/*Volvemos a mostrar el prompt después de imprimir el entorno*/
		}

		execute_command(args); /*Ejecuta el comando ingresado*/

		/*Libera la memoria usada por la entrada y los tokens*/
		free(line);
		free(args);


	} while (1);

	return (0);
}
