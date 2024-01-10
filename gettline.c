#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @info: parameter struct
 * @bf: address of buffer
 * @en: address of en var
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **bf, size_t *en)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*en) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*bf);
		*bf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(bf, &len_p, stdin);
#else
		r = _gettline(info, bf, &len_p);
#endif
		if (r > 0)
		{
			if ((*bf)[r - 1] == '\n')
			{
				(*bf)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*bf);
			build_history_list(info, *bf, info->histcount++);
			/* if (_strchr(*bf, ';')) is this a command chain? */
			{
				*en = r;
				info->cmd_buf = bf;
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
	static char *bf; /* the ';' command chain buffer */
	static size_t i, j, en;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &bf, &en);
	if (r == -1) /* EOF */
		return (-1);
	if (en)	/* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current bf position */
		p = bf + i; /* get pointer for return */

		check_chain(info, bf, &j, i, en);
		while (j < en) /* iterate to semicolon or end */
		{
			if (is_chain(info, bf, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= en) /* reached end of buffer? */
		{
			i = en = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buf_p = bf; /* else not a chain, pass back buffer from _gettline() */
	return (r); /* return length of buffer from _gettline() */
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @bf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buf(info_t *info, char *bf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, bf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _gettline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _gettline(info_t *info, char **ptr, size_t *length)
{
	static char bf[READ_BUF_SIZE];
	static size_t i, en;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == en)
		i = en = 0;

	r = read_buf(info, bf, &en);
	if (r == -1 || (r == 0 && en == 0))
		return (-1);

	c = _strchr(bf + i, '\n');
	k = c ? 1 + (unsigned int)(c - bf) : en;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, bf + i, k - i);
	else
		_strncpy(new_p, bf + i, k - i + 1);

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
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

