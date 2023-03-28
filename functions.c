#include "main.h"

/**
 * print_fct - to print strings
 * @c: an input string
 * @buf: buffer
 * @idx: returned index
 * @ml: maxlength
 * Return: nothing
 */
void print_fct(char c, void *buf, size_t idx, size_t ml)
{
	(void)idx;
	(void)ml;
	(void)buf;
	if (c)
	{
		_putchar(c);
	}
}

/**
 * print_buffer - prints characters
 * @c: value to be printed of type char
 * @buf: butffer to hold char
 * @idx: a general index
 * @ml: length of argument
 * Retrun: nothting
 */
void print_buffer(char c, void *buf, size_t idx, size_t ml)
{
	if (idx < ml)
	{
		((char *)buf)[idx] = c;
	}
}

/**
 * print_null - handles character casese
 * @c: character to function
 * @buffer: a buffer
 * @ml: max length
 * @idx: value for idx
 * Description - shortened
 */
void print_null(char c, void *buffer, size_t idx, size_t ml)
{
	(void)c;
	(void)buffer;
	(void)idx;
	(void)ml;
}
/**
 * _is_digit - checks if a character is a valid digit
 * @ch: input character
 * Return:  a bool
 */
bool _is_digit(char ch)
{
	return ((ch >= '0') && (ch <= '9'));
}

/**
 * _atoi - string to usigned int conversion
 * @str: input string to be converted
 * Return: an unsigned integer
 */
unsigned int _atoi(const char **str)
{
	unsigned int i = 0U;

	while (_is_digit(**str))
		i = i * 10U + (unsigned int)(*((*str)++) - '0');
	return (i);
}
