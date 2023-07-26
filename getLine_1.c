#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */

ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = nil;
	size_t len_p = nil;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(info, buf, &len_p);
#endif
		if (r > nil)
		{
			if ((*buf)[r - solo] == '\n')
			{
				(*buf)[r - solo] = '\0'; /* remove trailing newline */
				r--;
			}
			info->linecount_flag = solo;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * get_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */

ssize_t get_input(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t r = nil;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == n_solo) /* EOF */
		return (n_solo);
	if (len) /* we have commands left in the chain buffer */
	{
		j = i;		 /* init new iterator to current buf position */
		p = buf + i; /* get pointer for return */

		check_chain(info, buf, &j, i, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + solo;	  /* increment past nulled ';'' */
		if (i >= len) /* reached end of buffer? */
		{
			i = len = nil; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;			 /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (r);	  /* return length of buffer from _getline() */
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */

ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = nil;

	if (*i)
		return (nil);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= nil)
		*i = r;
	return (r);
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */

int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = nil, s = nil;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = nil;

	r = read_buf(info, buf, &len);
	if (r == n_solo || (r == nil && len == nil))
		return (n_solo);

	c = _strchr(buf + i, '\n');
	k = c ? solo + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + solo);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), n_solo : n_solo);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + solo);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */

void sigintHandler(__attribute__((unused)) int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
