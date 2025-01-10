#include "main.h"

/**
 * main - El punto de entrada para el programa shell
 *
 * Return: Siempre 0.
 */
int main(void)
{
	char *line, **args;

	do {
		if (isatty(STDIN_FILENO)) /*Muestra el prompt (modo interactivo)*/
		{
			printf("($) ");
		}

		line = read_input(); /*Lee la entrada del usuario*/

		if (line == NULL) /*Si llega (Ctrl+D), terminamos el shell*/
		{
			printf("\n");
			break;
		}

		args = parse_input(line); /*Procesa la entrada*/

		if (args[0] != NULL && strcmp(args[0], "exit") == 0) /*Si es "exit", salimos*/
		{
			handle_exit(args);
			free(line);
			free(args);
			break; /*Salimos del bucle y terminamos shell*/
		}

		if (args[0] != NULL && strcmp(args[0], "env") == 0) /*Si es "env", muestra el env*/
		{
			handle_env();
			free(line);
			free(args);
			continue;  /*Volvemos a mostrar el prompt*/
		}

		execute_command(args); /*Ejecuta el comando ingresado*/
		free(line); /*Libera memoria del line*/
		free(args); /*Libera memoria del args*/
	} while (1);

	return (0);
}
