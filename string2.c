#include "shell.h"

/**
 * _strcpyy - copies a string
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination
 */
char *_strcpyy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 * _strdup - duplicates a string
 * @sr: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *sr)
{
	int length = 0;
	char *ret;

	if (sr == NULL)
		return (NULL);
	while (*sr++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--sr;
	return (ret);
}

/**
 *_puts - prints an input string
 *@sr: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *sr)
{
	int i = 0;

	if (!sr)
		return;
	while (sr[i] != '\0')
	{
		_putchar(sr[i]);
		i++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

