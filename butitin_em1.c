#include "shell.h"

/**
 * _myhist - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myhist(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @info: parameter struct
 * @sr: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *sr)
{
	char *k, m;
	int ret;

	k = _strchr(sr, '=');
	if (!k)
		return (1);
	m = *k;
	*k = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, sr, -1)));
	*k = m;
	return (ret);
}

/**
 * set_alias - sets alias to string
 * @info: parameter struct
 * @sr: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *sr)
{
	char *k;

	k = _strchr(sr, '=');
	if (!k)
		return (1);
	if (!*++k)
		return (unset_alias(info, sr));

	unset_alias(info, sr);
	return (add_node_end(&(info->alias), sr, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *k = NULL, *a = NULL;

	if (node)
	{
		k = _strchr(node->sr, '=');
		for (a = node->sr; a <= k; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(k + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myalias(info_t *info)
{
	int i = 0;
	char *k = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		k = _strchr(info->argv[i], '=');
		if (k)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}

