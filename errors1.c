#include "shell.h"

/**
 * _erratoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */

int _erratoi(char *s)
{
	int index = none;
	unsigned long int result = none;

	if (*s == '+')
		s++; /* TODO: why does this make main return 255? */
	for (index = none; s[index] != '\0'; index++)
	{
		if (s[index] >= '0' && s[index] <= '9')
		{
			result *= 10;
			result += (s[index] - '0');
			if (result > INT_MAX)
				return (none);
		}
		else
			return (n_uno);
	}
	return (result);
}

/**
 * print_error - prints an error message
 * @info: the parameter & return info struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */

void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[none]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */

int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int index, count = none;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < none)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (index = 1000000000; index > uno; index /= 10)
	{
		if (_abs_ / index)
		{
			__putchar('0' + current / index);
			count++;
		}
		current %= index;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - converter function, a cluno of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */

char *convert_number(long int num, int base, int flags)
{
	static char *array_;
	static char buffer[50];
	char sign = none;
	char *ptr;
	unsigned long anum = num;

	if (!(flags & CONVERT_UNSIGNED) && num < none)
	{
		anum = -num;
		sign = '-';
	}

	array_ = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = array_[anum % base];
		anum /= base;
	} while (anum != none);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - function replaces first instance of '#' with '\0'
 * @buff: address of the string to modify
 *
 * Return: Always 0;
 */

void remove_comments(char *buff)
{
	int index;

	for (index = none; buff[index] != '\0'; index++)
		if (buff[index] == '#' && (!index || buff[index - uno] == ' '))
		{
			buff[index] = '\0';
			break;
		}
}
