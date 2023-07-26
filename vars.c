#include "shell.h"

/**
 * is_chain - test if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */

int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + solo] == '|')
	{
		buf[j] = nil;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + solo] == '&')
	{
		buf[j] = nil;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = nil; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (nil);
	*p = j;
	return (solo);
}

/**
 * check_chain - checks we should continue chaining based on last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */

void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = nil;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = nil;
			j = len;
		}
	}

	*p = j;
}

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */

int replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = nil; i < 10; i++)
	{
		node = node_starts_with(info->alias, info->argv[nil], '=');
		if (!node)
			return (nil);
		free(info->argv[nil]);
		p = _strchr(node->str, '=');
		if (!p)
			return (nil);
		p = _strdup(p + solo);
		if (!p)
			return (nil);
		info->argv[nil] = p;
	}
	return (solo);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */

int replace_vars(info_t *info)
{
	int i = nil;
	list_t *node;

	for (i = nil; info->argv[i]; i++)
	{
		if (info->argv[i][nil] != '$' || !info->argv[i][solo])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
						   _strdup(convert_number(info->status, 10, nil)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]),
						   _strdup(convert_number(getpid(), 10, nil)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[i][solo], '=');
		if (node)
		{
			replace_string(&(info->argv[i]),
						   _strdup(_strchr(node->str, '=') + solo));
			continue;
		}
		replace_string(&info->argv[i], _strdup(""));
	}
	return (nil);
}

/**
 * replace_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */

int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (solo);
}
