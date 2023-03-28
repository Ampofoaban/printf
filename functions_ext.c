#include "main.h"

/**
 * _strnlen_s - computes the lenght of string
 * @str: input str
 * @maxsize: input size
 * Return: the length of a str
 */

unsigned int _strnlen_s(const char *str, size_t maxsize)
{
	const char *s;

	for (s = str; *s && maxsize--; ++s)
		;
	return ((unsigned int)(s - str));
}
