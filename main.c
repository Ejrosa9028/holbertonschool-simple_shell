#include "main.h"

/**
 * main - Entry point for the shell program
 *
 * Return: Always 0.
 */
int main(void)
{
	char *line, **args;
	int execute_count = 0;

	do {
		if (isatty(STDIN_FILENO))
		{
			write(STDOUT_FILENO, "($) ", 4);
			fflush(stdout);
		}
		line = read_input(); /*Read user input*/

		if (line == NULL) /*If (Ctrl+D), exit the shell*/
		{
			if (isatty(STDIN_FILENO))
			{
				write(STDOUT_FILENO, "\n", 1);
			}
			break;
		}

		/* Limpiar la nueva línea al final de la entrada */
		if (line[strlen(line) - 1] == '\n')
		{
			line[strlen(line) - 1] = '\0'; /* Quitar el '\n' del final */
		}

		if (is_empty_or_spaces(line))
		{
			free(line);
			continue;
		}

		args = parse_input(line); /*Process input*/

		if (args == NULL || args[0] == NULL)
		{
			free(line);
			continue;  /*If it could not be analyzed, the prompt is displayed again.*/
		}

		if (args[0] != NULL && strcmp(args[0], "exit") == 0) /*If "exit, exit*/
		{
			handle_exit(args);
			free(line);
			free(args);
			break; /*Exit the loop and terminate shell*/
		}

		if (args[0] != NULL && strcmp(args[0], "env") == 0) /*If "env", show env*/
		{
			handle_env();
			free(line);
			free(args);
			continue;  /*Re-show prompt*/
		}

		if (args[0] != NULL && strcmp(args[0], "/bin/ls") == 0)
		{
			if (execute_count < 3)  /*Limitar a 3 ejecuciones*/
			{
				execute_count++;  /*Incrementar el contador*/
				execute_command(args);  /*Ejecutar el comando*/
			}
			else
			{
				printf("Se ha alcanzado el límite de ejecuciones de /bin/ls\n");
			}
		}
		else
		{
			execute_command(args);  /*Ejecutar cualquier otro comando*/
		}

		free(line); /*Free line memory*/
		free(args); /*Free args memory*/
	} while (1);

	return (0);
}
