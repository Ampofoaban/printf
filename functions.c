#include "main.h"

/**
 * handle_string_printing - to print strings
 * @str: an input string
 * Return: nothing
 */
int handle_string_printing(char *str)
{
	int i = 0;

	while (str[i] != '\0')
		_putchar(str[i++]);

	return (0);
}

/**
 * handle_print - prints characters
 * @character: value to be printed of type char
 * @buffer: butffer to hold char
 * @idx: a general index
 * @maxlen: length of argument
 * Retrun: nothting
 */
void handle_print(char character, void  *buffer, size_t idx, size_t maxlen)
{
	(void)buffer;
	(void)idx;
	(void)maxlen;

	if (character)
	{
		_putchar(character);

	}
}

/**
 * h_c - handles character casese
 * @pnt: print functio
 * @b: a buffer
 * @ml: max length
 * @i: value for idx
 * @f: value for format
 * @v: value for va list
 * Description - shortened
 */
void h_c(prnt_type pnt, char *b, size_t ml, size_t i, const char *f, va_list v)
{
	char c = (char)va_arg(v, int);

	pnt(c, b, i, ml);
	f++;
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
