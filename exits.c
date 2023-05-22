#include "shell.h"
/**
 *_strncpy - ...
 *@dest: ...
 *@src: ....
 *@n: ...
 *Return: ...
 */
char *_strncpy(char *dest, char *src, int n)
{
	int k, m;
	char *s = dest;

	k = 0;
	while (src[k] != '\0' && k < n - 1)
	{
		dest[k] = src[k];
		k++;
	}
	if (k < n)
	{
		m = k;
		while (m < n)
		{
			dest[m] = '\0';
			m++;
		}
	}
	return (s);
}

/**
 *_strncat - ...
 *@dest: ...
 *@src: ...
 *@n: ...
 *Return: ...
 */
char *_strncat(char *dest, char *src, int n)
{
	int k, m;
	char *s = dest;

	k = 0;
	m = 0;
	while (dest[k] != '\0')
		k++;
	while (src[m] != '\0' && m < n)
	{
		dest[k] = src[m];
		k++;
		m++;
	}
	if (m < n)
		dest[k] = '\0';
	return (s);
}

/**
 *_strchr - ...
 *@s: ...
 *@c: ...
 *Return: ..,
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
