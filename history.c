#include "shell.h"

/**
 * get_history_file - ...
 * @info: ...
 *
 * Return: ...
 */
char *get_history_file(info_t *info)
{
    char *buf, *dir;

    dir = _getenv(info, "HOME=");
    if (!dir)
        return NULL;

    buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
    if (!buf)
    {
        free(dir);
        return NULL;
    }

    buf[0] = '\0';
    _strcpy(buf, dir);
    _strcat(buf, "/");
    _strcat(buf, HIST_FILE);

    free(dir);
    return buf;
}

/**
 * write_history - ...
 * @info: ...
 *
 * Return: ...
 */
int write_history(info_t *info)
{
    ssize_t fd;
    char *filename = get_history_file(info);
    list_t *node = NULL;

    if (!filename)
        return -1;

    fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);
    free(filename);

    if (fd == -1)
        return -1;

    for (node = info->history; node; node = node->next)
    {
        _putsfd(node->str, fd);
        _putfd('\n', fd);
    }

    _putfd(BUF_FLUSH, fd);
    close(fd);
    return 1;
}

/**
 * read_history - ...
 * @info: ...
 *
 * Return: ...
 */
int read_history(info_t *info)
{
    int k, last = 0, linecount = 0;
    ssize_t fd, rdlen, fsize = 0;
    struct stat st;
    char *buf = NULL, *filename = get_history_file(info);

    if (!filename)
        return 0;

    fd = open(filename, O_RDONLY);
    free(filename);

    if (fd == -1)
        return 0;

    if (!fstat(fd, &st))
        fsize = st.st_size;

    if (fsize < 2)
        return 0;

    buf = malloc(sizeof(char) * (fsize + 1));
    if (!buf)
        return 0;

    rdlen = read(fd, buf, fsize);
    buf[fsize] = '\0';

    if (rdlen <= 0)
        return free(buf), 0;

    close(fd);

    for (k = 0; k < fsize; k++)
    {
        if (buf[k] == '\n')
        {
            buf[k] = '\0';
            build_history_list(info, buf + last, linecount++);
            last = k + 1;
        }
    }

    if (last != k)
        build_history_list(info, buf + last, linecount++);

    free(buf);
    info->histcount = linecount;

    while (info->histcount-- >= HIST_MAX)
        delete_node_at_index(&(info->history), 0);

    renumber_history(info);
    return info->histcount;
}

/**
 * build_history_list - ...
 * @info: ...
 * @buf: ...
 * @linecount: ...
 *
 * Return: ...
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
    list_t *node = NULL;

    if (info->history)
        node = info->history;

    add_node_end(&node, buf, linecount);

    if (!info->history)
        info->history = node;

    return 0;
}

/**
 * renumber_history - ...
 * @info: ...
 *
 * Return: ...
 */
int renumber_history(info_t *info)
{
    list_t *node = info->history;
    int k = 0;

    while (node)
    {
        node->num = k++;
        node = node->next;
    }

    return (info->histcount = k);
}

