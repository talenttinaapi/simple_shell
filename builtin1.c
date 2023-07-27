#include "shell.h"

/**
 * _myhistory - ...
 * @info: ...
 * Return: ...
 */
int _myhistory(info_t *info)
{
    print_list(info->history);
    return 0;
}

/**
 * unset_alias - ...
 * @info: ...
 * @str: ...
 * Return: ...
 */
int unset_alias(info_t *info, char *str)
{
    char *p, j;
    int ret;

    p = _strchr(str, '=');
    if (!p)
        return 1;

    j = *p;
    *p = 0;
    ret = delete_node_at_index(&(info->alias),
            get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
    *p = j;
    return ret;
}

/**
 * set_alias - ...
 * @info: ...
 * @str: ...
 * Return: ...
 */
int set_alias(info_t *info, char *str)
{
    char *p;

    p = _strchr(str, '=');
    if (!p)
        return 1;

    if (!*++p)
        return unset_alias(info, str);

    unset_alias(info, str);
    return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - ...
 * @node: ...
 * Return: ...
 */
int print_alias(list_t *node)
{
    char *p = NULL, *b = NULL;

    if (node)
    {
        p = _strchr(node->str, '=');
        for (b = node->str; b <= p; b++)
            _putchar(*b);

        _putchar('\'');
        _puts(p + 1);
        _puts("'\n");
        return 0;
    }

    return 1;
}

/**
 * _myalias - ...
 * @info: ...
 * Return: ...
 */
int _myalias(info_t *info)
{
    int k = 0;
    char *p = NULL;
    list_t *node = NULL;

    if (info->argc == 1)
    {
        node = info->alias;
        while (node)
        {
            print_alias(node);
            node = node->next;
        }
        return 0;
    }

    for (k = 1; info->argv[k]; k++)
    {
        p = _strchr(info->argv[k], '=');
        if (p)
            set_alias(info, info->argv[k]);
        else
            print_alias(node_starts_with(info->alias, info->argv[k], '='));
    }

    return 0;
}

