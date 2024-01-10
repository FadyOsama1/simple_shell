#include "shell.h"

/**
 * getenvir - returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **getenvir(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @vr: the string env vr property
 */
int _unsetenv(info_t *info, char *vr)
{
	list_t *node = info->env;
	size_t i = 0;
	char *k;

	if (!node || !vr)
		return (0);

	while (node)
	{
		k = starts_with(node->str, vr);
		if (k && *k == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @vr: the string env vr property
 * @valu: the string env vr valu
 *  Return: Always 0
 */
int _setenv(info_t *info, char *vr, char *valu)
{
	char *buf = NULL;
	list_t *node;
	char *k;

	if (!vr || !valu)
		return (0);

	buf = malloc(_strlen(vr) + _strlen(valu) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, vr);
	_strcat(buf, "=");
	_strcat(buf, valu);
	node = info->env;
	while (node)
	{
		k = starts_with(node->str, vr);
		if (k && *k == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}

