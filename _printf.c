#include "main.h"

/**
 * _printf -  implements the printf function in c
 * @format: first argument return by _printf
 * Return: desired formated inputs from the _printf function to screen
 */

int _printf(const char *format, ...)
{
	va_list va;
	char buffer[1];
	int result;

	va_start(va, format);
	result = _vprintf(handle_print, buffer, ((size_t)-1), format, va);
	va_end(va);

	return (result);
}

/**
 * _vprintf - handles various format specifiers
 * @fmt: first argument return by _printf
 * @va: other arguments returned by _printf
 * @buf: a character buffer
 * @ml: to store lengths
 * @prnt: to print characters
 * Return: 1 if no error occured
 */

int _vprintf(prnt_type prnt, char *buf, size_t ml, const char *fmt, va_list va)
{
	size_t idx = 0U;

	while (*fmt)
	{
		if (*fmt != '%')
		{
			prnt(*fmt, buf, idx, ml);
			fmt++;
			continue;
		}
		else
		{
			fmt++;
		}
		switch (*fmt)
		{
			case 'c':
			/*	h_c(prnt, buf, ml, idx, fmt, va);*/
				prnt((char)va_arg(va, int), buf, idx++, ml);
				fmt++;
				break;
			case 's':
				handle_string_printing(va_arg(va, char*));
				fmt++;
				break;
			case '%':
				prnt('%', buf, idx++, ml);
				fmt++;
				break;
			default:
				_putchar(*fmt);
				fmt++;
				break;
		}
	}
	return (0);
}
