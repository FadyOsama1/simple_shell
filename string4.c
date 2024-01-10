#include "shell.h"

/**
 * **strtow - splits a string into words. Repeat delimiters are ignored
 * @sr: the input string
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *sr, char *d)
{
	int i, j, k, q, numwords = 0;
	char **s;

	if (sr == NULL || sr[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; sr[i] != '\0'; i++)
		if (!is_delim(sr[i], d) && (is_delim(sr[i + 1], d) || !sr[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (is_delim(sr[i], d))
			i++;
		k = 0;
		while (!is_delim(sr[i + k], d) && sr[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (q = 0; q < k; q++)
			s[j][q] = sr[i++];
		s[j][q] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **strtow2 - splits a string into words
 * @sr: the input string
 * @d: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *sr, char d)
{
	int i, j, k, q, numwords = 0;
	char **s;

	if (sr == NULL || sr[0] == 0)
		return (NULL);
	for (i = 0; sr[i] != '\0'; i++)
		if ((sr[i] != d && sr[i + 1] == d) ||
		    (sr[i] != d && !sr[i + 1]) || sr[i + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (sr[i] == d && sr[i] != d)
			i++;
		k = 0;
		while (sr[i + k] != d && sr[i + k] && sr[i + k] != d)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (q = 0; q < k; q++)
			s[j][q] = sr[i++];
		s[j][q] = 0;
	}
	s[j] = NULL;
	return (s);
}

