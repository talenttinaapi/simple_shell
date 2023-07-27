#include "shell.h"

/**
 * _myexit - ...
 * @info: ...
 * Return: ...
 */
int _myexit(info_t *info)
{
    if (info->argv[1])
    {
        int exitcode = _erratoi(info->argv[1]);
        if (exitcode == -1)
        {
            info->status = 2;
            print_error(info, "Illegal number: ");
            _eputs(info->argv[1]);
            _eputchar('\n');
            return 1;
        }
        info->err_num = exitcode;
        return EXIT_SPECIAL;
    }

    info->err_num = -1;
    return EXIT_SPECIAL;
}

/**
 * _mycd - ...
 * @info: ...
 * Return: ...
 */
int _mycd(info_t *info)
{
    char *s, *dir, buffer[1024];
    int chdir_ret;

    s = getcwd(buffer, 1024);
    if (!s)
        _puts("TODO: >>getcwd failure emsg here<<\n");

    if (!info->argv[1])
    {
        dir = _getenv(info, "HOME=");
        if (!dir)
            chdir_ret = /*TODO: what should this be?*/ chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
        else
            chdir_ret = chdir(dir);
    }
    else if (_strcmp(info->argv[1], "-") == 0)
    {
        if (!_getenv(info, "OLDPWD="))
        {
            _puts(s);
            _putchar('\n');
            return 1;
        }
        _puts(_getenv(info, "OLDPWD=")), _putchar('\n');
        chdir_ret = /*TODO: what should this be?*/ chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
    }
    else
    {
        chdir_ret = chdir(info->argv[1]);
    }

    if (chdir_ret == -1)
    {
        print_error(info, "can't cd to ");
        _eputs(info->argv[1]), _eputchar('\n');
    }
    else
    {
        _setenv(info, "OLDPWD", _getenv(info, "PWD="));
        _setenv(info, "PWD", getcwd(buffer, 1024));
    }

    return 0;
}

/**
 * _myhelp - ...
 * @info: ...
 * Return: ...
 */
int _myhelp(info_t *info)
{
    char **arg_array;

    arg_array = info->argv;
    // TODO: Implement help functionality
    _puts("help call works. Function not yet implemented \n");
    if (0)
        _puts(*arg_array);

    return 0;
}

/**
 * populate_env_list - ...
 * @info: ...
 * Return: ...
 */
int populate_env_list(info_t *info)
{
    list_t *node = NULL;
    size_t k;

    for (k = 0; environ[k]; k++)
        add_node_end(&node, environ[k], 0);

    info->env = node;
    return 0;
}

