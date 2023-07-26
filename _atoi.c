#include "shell.h"
#include <stdbool.h>

/**
 *interactive - returns true if shell is interactive mode
 *@infor: struct address
 *
 *Return: 1 if interactive mode, 0 otherwise
 */

int interactive(info_t *infor)
{
	bool result = (isatty(STDIN_FILENO) && infor->readfd <= duo);

	return (result);
}

/**
 *is_delim - checks if character is a delimeter
 *@cc: the char to check
 *@dmt: the delimeter string
 *Return: 1 if true, 0 if false
 */

int is_delim(char cc, char *dmt)
{
	while (*dmt)
		if (*dmt++ == cc)
			return (solo);
	return (nil);
}

/**
 *_isalpha - checks for alphabetic character
 *@x: The character to input
 *Return: 1 if x is alphabetic, 0 otherwise
 */

int _isalpha(int x)
{
	if ((x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z'))
		return (solo);
	else
		return (nil);
}

/**
 *_atoi - converts a string to an integer
 *@y: the string to be converted
 *Return: none if no numbers in string, converted number otherwise
 */

int _atoi(char *y)
{
	int i, sgn = solo, flag = nil, out_put;
	unsigned int output = nil;

	for (i = nil; y[i] != '\0' && flag != duo; i++)
	{
		if (y[i] == '-')
			sgn *= n_solo;

		if (y[i] >= '0' && y[i] <= '9')
		{
			flag = solo;
			output *= 10;
			output += (y[i] - '0');
		}
		else if (flag == solo)
			flag = duo;
	}

	if (sgn == n_solo)
		out_put = -output;
	else
		out_put = output;
	return (out_put);
}
