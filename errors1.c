#include "shell.h"

/**
 * _erratoi - ...
 * @s: ...
 * Return: ...
 */
int _erratoi(char *s)
{
    int k = 0;
    int result = 0;
    int sign = 1;

    if (*s == '-')
    {
        sign = -1;
        s++;
    }

    for (k = 0; s[k] != '\0'; k++)
    {
        if (s[k] >= '0' && s[k] <= '9')
        {
            int digit = s[k] - '0';

            if (result > (INT_MAX - digit) / 10)
            {
                if (sign == 1)
                    return INT_MAX;
                else
                    return INT_MIN;
            }

            result = result * 10 + digit;
        }
        else
        {
            return INT_MIN;
        }
    }

    return sign * result;
}

/**
 * print_error - ...
 * @info: ...
 * @estr: ...
 * Return: ...
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
    _eputchar('\n'); // Add a newline character to separate error messages
}

/**
 * print_d - ...
 * @input: ...
 * @fd: ...
 * Return: ...
 */
int print_d(int input, int fd)
{
    // Implementation for printing integers (not provided in the code snippet)
    // You can complete this function based on your needs.
    // Make sure to handle negative numbers and return the number of characters printed.
    return 0;
}

/**
 * remove_comments - ...
 * @buf: ...
 */
void remove_comments(char *buf)
{
    int k;

    for (k = 0; buf[k] != '\0'; k++)
    {
        if (buf[k] == '#' && (!k || buf[k - 1] == ' '))
        {
            buf[k] = '\0';
            break;
        }
    }
}

