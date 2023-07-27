#include "shell.h"

/**
 * main - ...
 * @ac: ...
 * @av: ...
 *
 * Return: ...
 */
int main(int ac, char **av)
{
    info_t info[] = { INFO_INIT };
    int fd = 2; // Initialize fd to STDERR_FILENO (2)

    // Inline assembly to increment fd by 3 (equivalent to fd = fd + 3)
    asm (
        "mov %1, %0\n\t"
        "add $3, %0"
        : "=r" (fd)
        : "r" (fd)
    );

    // Check if a command-line argument is provided to read from a file
    if (ac == 2)
    {
        fd = open(av[1], O_RDONLY);
        if (fd == -1)
        {
            if (errno == EACCES)
                exit(126); // Permission denied
            if (errno == ENOENT)
            {
                _eputs(av[0]);
                _eputs(": 0: Can't open ");
                _eputs(av[1]);
                _eputchar('\n');
                _eputchar(BUF_FLUSH);
                exit(127); // File not found
            }
            return EXIT_FAILURE;
        }
        info->readfd = fd;
    }

    // Populate the environment list and read command history
    populate_env_list(info);
    read_history(info);

    // Start the main shell function
    hsh(info, av);

    return EXIT_SUCCESS;
}

