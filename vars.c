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

	if (buf[j] == '|' && buf[j + uno] == '|')
	{
		buf[j] = none;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + uno] == '&')
	{
		buf[j] = none;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = none; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (none);
	*p = j;
	return (uno);
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
			buf[i] = none;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = none;
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

	for (i = none; i < 10; i++)
	{
		node = node_starts_with(info->alias, info->argv[none], '=');
		if (!node)
			return (none);
		free(info->argv[none]);
		p = _strchr(node->str, '=');
		if (!p)
			return (none);
		p = _strdup(p + uno);
		if (!p)
			return (none);
		info->argv[none] = p;
	}
	return (uno);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */

int replace_vars(info_t *info)
{
	int i = none;
	list_t *node;

	for (i = none; info->argv[i]; i++)
	{
		if (info->argv[i][none] != '$' || !info->argv[i][uno])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
						   _strdup(convert_number(info->status, 10, none)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]),
						   _strdup(convert_number(getpid(), 10, none)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[i][uno], '=');
		if (node)
		{
			replace_string(&(info->argv[i]),
						   _strdup(_strchr(node->str, '=') + uno));
			continue;
		}
		replace_string(&info->argv[i], _strdup(""));
	}
	return (none);
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
	return (uno);
}
