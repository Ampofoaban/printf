#include "main.h"
/**
 * _printf -  implements the printf function in c
 * @format: first argument return by _printf
 * Return: desired formated inputs from the _printf function to screen
 */

int _printf(const char *format, ...)
{
	va_list va;
	int result;

	va_start(va, format);
	result = _printfsub(format, va);

	va_end(va);

	return (result);
}

/**
 * _printfsub - handles various format specifiers
 * @format: first argument return by _printf
 * @va: other arguments returned by _printf
 * Return: 1 if no error occured
 */

int _printfsub(const char *format, va_list va)
{
	while (*format)
	{
		if (*format != '%')
		{
			_putchar(*format);
			format++;
			continue;
		}
		else
		{
			format++;
		}

		switch (*format)
		{
			case 'c':
				{
					char character = (char)va_arg(va, int);

					if (character)
						_putchar(character);
					format++;
					break;
				}
			case 's':
				{
					char *str = va_arg(va, char*);

					handle_string_printing(str);
					format++;
					break;
				}
			default:
				_putchar(*format);
				format++;
				break;
		}
	}
	return (0);
}
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
