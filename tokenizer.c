#include "shell.h"

/**
 * strtow - ...
 * @str:  Input string to be split
 * @d:    Delimiter string used to split the input string
 *
 * Return: Pointer to an array of strings (words) created from the input
 *         string, split using the specified delimiter. The last element of
 *         the array is set to NULL.
 */
char **strtow(char *str, char *d)
{
        int k, j, v, m, numwords = 0;
        char **s;

        if (str == NULL || str[0] == '\0')
                return (NULL);

        if (!d)
                d = " ";

        // Count the number of words
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
                // Skip leading delimiters
                while (is_delim(str[k], d))
                        k++;

                v = 0;
                // Find the end of the current word
                while (!is_delim(str[k + v], d) && str[k + v])
                        v++;

                s[j] = malloc((v + 1) * sizeof(char));
                if (!s[j])
                {
                        // Free the allocated memory and return NULL if malloc fails
                        for (v = 0; v < j; v++)
                                free(s[v]);
                        free(s);
                        return (NULL);
                }

                // Copy the word into the array
                for (m = 0; m < v; m++)
                        s[j][m] = str[k++];
                s[j][m] = '\0';
        }
        s[j] = NULL;
        return (s);
}

/**
 * strtow2 - ...
 * @str:  Input string to be split
 * @d:    Delimiter character used to split the input string
 *
 * Return: Pointer to an array of strings (words) created from the input
 *         string, split using the specified delimiter character. The last
 *         element of the array is set to NULL.
 */
char **strtow2(char *str, char d)
{
        int k, j, v, m, numwords = 0;
        char **s;

        if (str == NULL || str[0] == '\0')
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
                // Skip leading delimiters
                while (str[k] == d && str[k] != '\0')
                        k++;

                v = 0;
                // Find the end of the current word
                while (str[k + v] != d && str[k + v] && str[k + v] != d)
                        v++;

                s[j] = malloc((v + 1) * sizeof(char));
                if (!s[j])
                {
                        // Free the allocated memory and return NULL if malloc fails
                        for (v = 0; v < j; v++)
                                free(s[v]);
                        free(s);
                        return (NULL);
                }

                // Copy the word into the array
                for (m = 0; m < v; m++)
                        s[j][m] = str[k++];
                s[j][m] = '\0';
        }
        s[j] = NULL;
        return (s);
}

