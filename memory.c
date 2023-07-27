#include "shell.h"

/**
 * bfree - ...
 * @ptr: Pointer to the memory to be freed
 *
 * This function frees memory that was previously allocated using `malloc`.
 * After freeing the memory, it sets the pointer to `NULL`.
 *
 * Return: 1 if memory was freed successfully, 0 otherwise
 */
int bfree(void **ptr)
{
    if (ptr && *ptr)
    {
        free(*ptr);
        *ptr = NULL;
        return 1; // Memory freed successfully
    }
    return 0; // Memory was not freed
}

