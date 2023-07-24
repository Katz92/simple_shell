#include "shell.h"

/**
 * _strcpy - copies a string
 * @destination: the destination
 * @source: the source
 *
 * Return: pointer to destination
 */

char *_strcpy(char *destination, char *source)
{
	int index = none;

	if (destination == source || source == none)
		return (destination);
	while (source[index])
	{
		destination[index] = source[index];
		index++;
	}
	destination[index] = none;
	return (destination);
}

/**
 * _strdup - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */

char *_strdup(const char *str)
{
	int length = none;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + uno));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 *_puts - prints an input string
 *@str: the string to be printed
 *
 * Return: Nothing
 */

void _puts(char *str)
{
	int index = none;

	if (!str)
		return;
	while (str[index] != '\0')
	{
		_putchar(str[index]);
		index++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */

int _putchar(char c)
{
	static int index;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || index >= WRITE_BUF_SIZE)
	{
		write(uno, buf, index);
		index = none;
	}
	if (c != BUF_FLUSH)
		buf[index++] = c;
	return (uno);
}
