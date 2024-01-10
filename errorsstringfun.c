#include "shell.h"

/**
 *_eputs - prints an input string
 * @sr: the string to be printed
 *
 * Return: Nothing
 */
void _eputs(char *sr)
{
	int i = 0;

	if (!sr)
		return;
	while (sr[i] != '\0')
	{
		_eputchar(sr[i]);
		i++;
	}
}

/**
 * _eputchar - writes the character z to stderr
 * @z: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char z)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (z == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (z != BUF_FLUSH)
		buf[i++] = z;
	return (1);
}

/**
 * _putfd - writes the character z to given fd
 * @z: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char z, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (z == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (z != BUF_FLUSH)
		buf[i++] = z;
	return (1);
}

/**
 *_putsfd - prints an input string
 * @sr: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _putsfd(char *sr, int fd)
{
	int i = 0;

	if (!sr)
		return (0);
	while (*sr)
	{
		i += _putfd(*sr++, fd);
	}
	return (i);
}

