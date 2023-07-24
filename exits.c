#include "shell.h"

/**
 **_strncpy - copies a string
 *@dest: the destination string to be copied to
 *@src: the source string
 *@n: the amount of characters to be copied
 *Return: the concatenated string
 */

char *_strncpy(char *dest, char *src, int n)
{
	int a_i, a_j;
	char *dest_str = dest;

	a_i = 0;
	while (src[a_i] != '\0' && a_i < n - 1)
	{
		dest[a_i] = src[a_i];
		a_i++;
	}
	if (a_i < n)
	{
		a_j = a_i;
		while (a_j < n)
		{
			dest[a_j] = '\0';
			a_j++;
		}
	}
	return (dest_str);
}

/**
 **_strncat - concatenates duo strings
 *@dest: the first string
 *@src: the second string
 *@n: the amount of bytes to be maximally used
 *Return: the concatenated string
 */

char *_strncat(char *dest, char *src, int n)
{
	int index, j_num;
	char *s = dest;

	index = j_num = 0;
	while (dest[index] != '\0')
		index++;
	while (src[j_num] != '\0' && j_num < n)
	{
		dest[index] = src[j_num];
		index++;
		j_num++;
	}
	if (j_num < n)
		dest[index] = '\0';
	return (s);
}

/**
 **_strchr - locates a character in a string
 *@s: the string to be parsed
 *@c: the character to look for
 *Return: (s) a pointer to the memory area s
 */

char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
