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
