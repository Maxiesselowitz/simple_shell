#include "shell.h"

/**
 * input_buf - it buffers the chained commands
 *
 * @info: the parameter struct
 *
 * @buf: the address struct
 *
 * @len: the address of the length variable
 *
 * Return: the bytes read
 */

ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	ssize_t len_p = 0;

	if (!*len) /* if buffer empty, fill it */
	{
		/*bufree((void **)info->cmd_buf); */
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* removes trailing newline */
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->historycount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * get_input - it gets a line without new line
 *
 * @info: the parameter struct
 *
 * Return: the bytes read
 */

ssize_t get_input(info_t *info)
{
	static char *buf; /* the ; command chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);

	if (r == -1) /* EOF */
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		check_chain(info, buf, &j, i len);

		while (j < len)
		{
			if (is_chain(info, buf, &jj))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = cmd_norm;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (r);
}

/**
 * read_buf - it reads a buffer
 *
 * @info: the parameter struct
 *
 * @buf: the buffer
 *
 * @i: the size
 *
 * Return: r
 */

ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);

	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - it gets the next line of input
 *
 * @info: the parameter struct
 *
 * @ptr: the address of the pointer to buffer
 *
 * @length: the size of preallocated buffer
 *
 * Return: s
 */

int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;

	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);

	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + 1, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = realloc(p, s, s ? s + k : k + 1);

	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncat(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;

	*ptr = p;
	return (s);
}

/**
 * sigintHandler - it block ctrl + C
 *
 * @sig_num: the signal nnumber
 *
 * Return: void
 */

void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("S ");
	_putchar(BUF_FLUSH);
}
