#include "shell.h"

/**
 * _memset - it fills memory with a constraint byte
 *
 * @s: the pointer to the memory area
 *
 * @b: the byte to fill
 *
 * @n: the amount of bytes to be filled
 *
 * Return: s a pointer to the memory area
 */

char _memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * ffree - it frees a string of strings
 *
 * @pp: the strign of strings
 */

void ffree(char **pp)
{
	char **a = pp;

	if (!p)
		return;

	while (*pp)
		free(**pp++);
	free(a);
}

/**
 * _realloc - it reallocates a block of memory
 *
 * @ptr: the pointer to the previous malloc block
 *
 * @old_size: the byte size of the previous block
 *
 * @new_size: the byte size of the new block
 *
 * Return: the pointer to the block
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));

	if (!new_size)
		return (free(ptr), NULL);

	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);

	if (!p)
		return (NULL);

	old_size = old_size > new_size ? old_size : new_size;

	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
