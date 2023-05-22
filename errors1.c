#include "shell.h"
/**
 *_erratoi - ...
 *@s: ...
 *Return: ...
 *
 */
int _erratoi(char *s)
{
	int k = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (k = 0;  s[k] != '\0'; k++)
	{
		if (s[k] >= '0' && s[k] <= '9')
		{
			result *= 10;
			result += (s[k] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 *print_error - ...
 *@info: ...
 *@estr: ...
 *Return: ...
 *
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 *print_d - ...
 *@input: ...
 *@fd: ...
 *
 *Return: ...
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int k, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (k = 1000000000; k > 1; k /= 10)
	{
		if (_abs_ / k)
		{
			__putchar('0' + current / k);
			count++;
		}
		current %= k;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 *convert_number - ...
 *@num: ...
 *@base: ...
 *@flags: ...
 *
 *Return: ...
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long j = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		j = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[j % base];
		j /= base;
	} while (j != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 *remove_comments - ...
 *@buf: ...
 *
 *Return: ...
 */
void remove_comments(char *buf)
{
	int k;

	for (k = 0; buf[k] != '\0'; k++)
		if (buf[k] == '#' && (!k || buf[k - 1] == ' '))
		{
			buf[k] = '\0';
			break;
		}
}
