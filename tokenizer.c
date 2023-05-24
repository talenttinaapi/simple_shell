#include "shell.h"
/**
 **strtow - ...
 *@str: ...
 *@d: ...
 *Return: ...
 */
char **strtow(char *str, char *d)
{
	int k, j, v, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (k = 0; str[k] != '\0'; k++)
		if (!is_delim(str[k], d) && (is_delim(str[k + 1], d) || !str[k + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (k = 0, j = 0; j < numwords; j++)
	{
		while (is_delim(str[k], d))
			k++;
		v = 0;
		while (!is_delim(str[k + v], d) && str[k + v])
			v++;
		s[j] = malloc((v + 1) * sizeof(char));
		if (!s[j])
		{
			for (v = 0; v < j; v++)
				free(s[v]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < v; m++)
			s[j][m] = str[k++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
/**
 **strtow2 - ...
 *@str: ...
 *@d: ...
 *Return: ...
 */
char **strtow2(char *str, char d)
{
	int k, j, v, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (k = 0; str[k] != '\0'; k++)
		if ((str[k] != d && str[k + 1] == d) ||
				    (str[k] != d && !str[k + 1]) || str[k + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (k = 0, j = 0; j < numwords; j++)
	{
		while (str[k] == d && str[k] != d)
			k++;
		v = 0;
		while (str[k + v] != d && str[k + v] && str[k + v] != d)
			v++;
		s[j] = malloc((v + 1) * sizeof(char));
		if (!s[j])
		{
			for (v = 0; v < j; v++)
				free(s[v]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < v; m++)
			s[j][m] = str[k++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
