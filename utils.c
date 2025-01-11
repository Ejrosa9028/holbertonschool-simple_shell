#include "main.h"

/**
 * is_empty_or_spaces - Checks if a string is empty or contains only spaces.
 * @str: The string to check.
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
		if (str[i] != ' ' && str[i] != '\t')  /* Si hay algo que no es espacio */
			return (0);
	}
	return (1); /* La cadena está vacía o solo tiene espacios */
}

/**
 * is_whitespace - Checks if a character is a whitespace character.
 * @c: The character to check.
 *
 * Return: 1 if the character is whitespace, 0 otherwise.
 */
int is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' ||
			c == '\r' || c == '\v' || c == '\f');
}

/**
 * trim_spaces - Removes leading and trailing spaces from a string.
 * @str: The string to trim.
 *
 * Return: The trimmed string.
 */
char *trim_spaces(char *str)
{
	char *end;

	while (*str && is_whitespace(*str))
	{ /*Elimina los espacios iniciales */
		str++;
	}

	if (*str == 0)
		return (str);

	end = str + strlen(str) - 1;

	while (is_whitespace(*end))
	{ /*Eliminar los espacios finales */
		end--;
	}

	*(end + 1) = '\0'; /* Agregsr el termino nulo al final de la cadena */
	return (str);
}

/**
 * normalize_path - Normalizes a file path by removing consecutive slashes.
 * @path: The path to normalize.
 *
 * Return: Nothing.
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
				src++; /*Saltar barras consecutiivas */
		}
		src++;
		dst++;
	}
	*dst = '\0';
}
