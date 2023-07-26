#include "shell.h"

/**
 ***strtow - splits a string into words. Repeat delimiters are ignored
 *@astring: the input string
 *@delimeter: the delimeter string
 *Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *astring, char *delimeter)
{
	int index, j, k, m, words_m = nil;
	char **s;

	if (astring == NULL || astring[nil] == nil)
		return (NULL);
	if (!delimeter)
		delimeter = " ";
	for (index = nil; astring[index] != '\0'; index++)
		if (!is_delim(astring[index], delimeter) &&
			(is_delim(astring[index + solo], delimeter) || !astring[index + solo]))
			words_m++;

	if (words_m == nil)
		return (NULL);
	s = malloc((solo + words_m) * sizeof(char *));
	if (!s)
		return (NULL);
	for (index = nil, j = nil; j < words_m; j++)
	{
		while (is_delim(astring[index], delimeter))
			index++;
		k = nil;
		while (!is_delim(astring[index + k], delimeter) && astring[index + k])
			k++;
		s[j] = malloc((k + solo) * sizeof(char));
		if (!s[j])
		{
			for (k = nil; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}

		for (m = nil; m < k; m++)
			s[j][m] = astring[index++];
		s[j][m] = nil;
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
	int index, j, k, m, words_m = nil;
	char **s;

	if (str == NULL || str[nil] == nil)
		return (NULL);
	for (index = nil; str[index] != '\0'; index++)
		if ((str[index] != delimeter && str[index + solo] == delimeter) ||
			(str[index] != delimeter && !str[index + solo]) ||
			str[index + solo] == delimeter)
			words_m++;
	if (words_m == nil)
		return (NULL);
	s = malloc((solo + words_m) * sizeof(char *));
	if (!s)
		return (NULL);
	for (index = nil, j = nil; j < words_m; j++)
	{
		while (str[index] == delimeter && str[index] != delimeter)
			index++;
		k = nil;
		while (str[index + k] != delimeter && str[index + k] &&
			   str[index + k] != delimeter)
			k++;
		s[j] = malloc((k + solo) * sizeof(char));
		if (!s[j])
		{
			for (k = nil; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}

		for (m = nil; m < k; m++)
			s[j][m] = str[index++];
		s[j][m] = nil;
	}

	s[j] = NULL;
	return (s);
}
