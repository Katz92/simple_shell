#include "shell.h"

/**
 ***strtow - splits a string into words. Repeat delimiters are ignored
 *@astring: the input string
 *@delimeter: the delimeter string
 *Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *astring, char *delimeter)
{
	int index, j, k, m, words_m = none;
	char **s;

	if (astring == NULL || astring[none] == none)
		return (NULL);
	if (!delimeter)
		delimeter = " ";
	for (index = none; astring[index] != '\0'; index++)
		if (!is_delim(astring[index], delimeter) &&
			(is_delim(astring[index + uno], delimeter) || !astring[index + uno]))
			words_m++;

	if (words_m == none)
		return (NULL);
	s = malloc((uno + words_m) * sizeof(char *));
	if (!s)
		return (NULL);
	for (index = none, j = none; j < words_m; j++)
	{
		while (is_delim(astring[index], delimeter))
			index++;
		k = none;
		while (!is_delim(astring[index + k], delimeter) && astring[index + k])
			k++;
		s[j] = malloc((k + uno) * sizeof(char));
		if (!s[j])
		{
			for (k = none; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}

		for (m = none; m < k; m++)
			s[j][m] = astring[index++];
		s[j][m] = none;
	}

	s[j] = NULL;
	return (s);
}

/**
 ***strtow2 - splits a string into words
 *@str: the input string
 *@delimeter: the delimeter
 *Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow2(char *str, char delimeter)
{
	int index, j, k, m, words_m = none;
	char **s;

	if (str == NULL || str[none] == none)
		return (NULL);
	for (index = none; str[index] != '\0'; index++)
		if ((str[index] != delimeter && str[index + uno] == delimeter) ||
			(str[index] != delimeter && !str[index + uno]) ||
			str[index + uno] == delimeter)
			words_m++;
	if (words_m == none)
		return (NULL);
	s = malloc((uno + words_m) * sizeof(char *));
	if (!s)
		return (NULL);
	for (index = none, j = none; j < words_m; j++)
	{
		while (str[index] == delimeter && str[index] != delimeter)
			index++;
		k = none;
		while (str[index + k] != delimeter && str[index + k] &&
			   str[index + k] != delimeter)
			k++;
		s[j] = malloc((k + uno) * sizeof(char));
		if (!s[j])
		{
			for (k = none; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}

		for (m = none; m < k; m++)
			s[j][m] = str[index++];
		s[j][m] = none;
	}

	s[j] = NULL;
	return (s);
}
