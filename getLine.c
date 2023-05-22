#include "shell.h"
/**
 *input_buf - ...
 *@info: ...
 *@buf: ...
 *@len: ...
 *
 *Return: ...
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t z = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		z = getline(buf, &len_p, stdin);
#else
		z = _getline(info, buf, &len_p);
#endif
		if (z > 0)
		{
			if ((*buf)[z - 1] == '\n')
			{
				(*buf)[z - 1] = '\0';
				z--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = z;
				info->cmd_buf = buf;
			}
		}
	}
	return (z);
}

/**
 *get_input - ...
 *@info: ...
 *
 *Return: ...
 */
ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t k, j, len;
	ssize_t z = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	z = input_buf(info, &buf, &len);
	if (z == -1) /* EOF */
		return (-1);
	if (len)
	{
		j = k; /* init new iterator to current buf position */
		p = buf + k; /* get pointer for return */

		check_chain(info, buf, &j, k, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		k = j + 1; /* increment past nulled ';'' */
		if (k >= len) /* reached end of buffer? */
		{
			k = len = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current cmd position */
		return (_strlen(p)); /* return length of current cmd */
	}

	*buf_p = buf;
	return (z); /* return length of buffer from _getline() */
}

/**
 *read_buf - ...
 *@info: ...
 *@buf: ...
 * @i: ...
 *
 *Return: ...
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t z = 0;

	if (*i)
		return (0);
	z = read(info->readfd, buf, READ_BUF_SIZE);
	if (z >= 0)
		*i = z;
	return (z);
}

/**
 *_getline - ...
 *@info: ...
 *@ptr: ...
 *@length: ...
 *
 *Return: ...
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t k, len;
	size_t v;
	ssize_t z = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (k == len)
		k = len = 0;

	z = read_buf(info, buf, &len);
	if (z == -1 || (z == 0 && len == 0))
		return (-1);

	c = _strchr(buf + k, '\n');
	v = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + v : v + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + k, v - k);
	else
		_strncpy(new_p, buf + k, v - k + 1);

	s += v - k;
	k = v;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}
/**
 *sigintHandler - ...
 *@sig_num: ...
 *
 *Return: ...
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
