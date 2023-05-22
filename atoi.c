#include "shell.h"

/**
 * interactive - ...
 * @info: ...
 *
 * Return: ...
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - ...
 * @c: ...
 * @delim: ...
 * Return: ...
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _isalpha - ...
 * @c: ...
 * Return: ...
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - ...
 * @s: ...
 * Return: ...
 */

int _atoi(char *s)
{
	int k, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (k = 0; s[k] != '\0' && flag != 2; k++)
	{
		if (s[k] == '-')
			sign *= -1;

		if (s[k] >= '0' && s[k] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[k] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}

