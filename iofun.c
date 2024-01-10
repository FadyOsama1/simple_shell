#include "shell.h"

/**
 * gethistfile - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containg history file
 */

char *gethistfile(info_t *info)
{
	char *bf, *der;

	der = _getenv(info, "HOME=");
	if (!der)
		return (NULL);
	bf = malloc(sizeof(char) * (_strlen(der) + _strlen(HIST_FILE) + 2));
	if (!bf)
		return (NULL);
	bf[0] = 0;
	_strcpy(bf, der);
	_strcat(bf, "/");
	_strcat(bf, HIST_FILE);
	return (bf);
}

/**
 * writehist - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int writehist(info_t *info)
{
	ssize_t fd;
	char *filename = gethistfile(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * readhist - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int readhist(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *bf = NULL, *filename = gethistfile(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	bf = malloc(sizeof(char) * (fsize + 1));
	if (!bf)
		return (0);
	rdlen = read(fd, bf, fsize);
	bf[fsize] = 0;
	if (rdlen <= 0)
		return (free(bf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (bf[i] == '\n')
		{
			bf[i] = 0;
			buildhistlist(info, bf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		buildhistlist(info, bf + last, linecount++);
	free(bf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumberhist(info);
	return (info->histcount);
}

/**
 * buildhistlist - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @bf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int buildhistlist(info_t *info, char *bf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, bf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumberhist - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumberhist(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}

