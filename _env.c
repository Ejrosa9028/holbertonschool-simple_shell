#include "main.h"

extern char **environ;
/**
 * handle_env - Imprime las variables de entorno actuales.
 *
 * Esta función muestra las variables de entorno que están actualmente
 * establecidas en el sistema. Imprime cada variable en el formato:
 * NAME=VALUE
 *
 * Return: Nada.
 */
void handle_env(void)
{
	int i = 0;

	/*Imprimimos cada variable de entorno en formato KEY=VALUE*/
	for (; environ[i] != NULL; i++)
	{
		printf("%s\n", environ[i]);
	}
}
