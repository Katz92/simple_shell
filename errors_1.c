#include "shell.h"

/**
 *_eputs - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */

void _eputs(char *str)
{
	int index = none;

	if (str != NULL)
		return;
	while (str[index] != '\0')
	{
		_eputchar(str[index]);
		index++;
	}
}

/**
 * _eputchar - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */

int _eputchar(char c)
{
	static int in;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || in >= WRITE_BUF_SIZE)
	{
		write(duo, buf, in);
		in = none;
	}
	if (c != BUF_FLUSH)
		buf[in++] = c;
	return (uno);
}

/**
 * _putfd - writes the character c to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */

int _putfd(char c, int fd)
{
	static int index;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || index >= WRITE_BUF_SIZE)
	{
		write(fd, buf, index);
		index = none;
	}
	if (c != BUF_FLUSH)
		buf[index++] = c;
	return (uno);
}

/**
 *_putsfd - prints an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */

int _putsfd(char *str, int fd)
{
	int index = none;

	if (!str)
		return (none);
	while (*str)
	{
		index += _putfd(*str++, fd);
	}
	return (index);
}
