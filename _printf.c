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
	result = _vprintf(print_fct, buffer, ((size_t)-1), format, va);
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
	unsigned int n, width, precision, flags;

	while (*fmt)
	{
		if (*fmt != '%')
		{
			prnt(*fmt, buf, idx++, ml);
			fmt++;
			continue;
		}
		else
		{
			fmt++;
		}

		flags = 0U;
		do {
			switch (*fmt)
			{
				case ' ':
					flags |= FLAGS_SPACE;
					fmt++;
					n = 1U;
					break;
				case '+':
					flags |= FLAGS_PLUS;
					fmt++;
					n = 1U;
					break;
				case '-':
					flags |= FLAGS_LEFT;
					fmt++;
					n = 1U;
					break;
				case '0':
					flags |= FLAGS_ZEROPAD;
					fmt++;
					n = 1U;
					break;
				case '#':
					flags |= FLAGS_HASH;
					fmt++;
					n = 1U;
					break;
				default:
					n = 0U;
					break;
			}
		} while (n);

		width = 0U;
		if (_is_digit(*fmt))
		{
			width = _atoi(&fmt);
		}
		else if (*fmt == '*')
		{
			fmt++;
		}

		precision = 0U;
		if (*fmt == '.')
		{
			flags |= FLAGS_PRECISION;
			fmt++;
			if (_is_digit(*fmt))
			{
				precision = _atoi(&fmt);
			}
			else if (*fmt == '*')
			{
				const int prec = (int)va_arg(va, int);
				precision = prec > 0 ? (unsigned int)prec : 0U;
				fmt++;
			}
		}
		switch (*fmt)
		{
			case 'c':
				{
					unsigned int l = 1U;

					if (!(flags & FLAGS_LEFT))
					{
						while (l++ < width)
						{
							prnt(' ', buf, idx++, ml);
						}
					}
					/*h_c(prnt, buf, ml, idx, fmt, va);*/
					prnt((char)va_arg(va, int), buf, idx++, ml);

					if (flags & FLAGS_LEFT)
					{
						while (l++ < width)
						{
							prnt(' ', buf, idx++, ml);
						}
					}
					fmt++;
					break;
				}
			case 's':
				{
					const char *p = va_arg(va, char*);
					unsigned int l = _strnlen_s(p, precision ? precision : (size_t)-1);
					 printf("came hereand crashed %c\n", *fmt);
					if (flags & FLAGS_PRECISION)
					{
						l = (l < precision ? l : precision);
					}
					if (!(flags & FLAGS_LEFT))
					{
						while (l++ < width)
						{
							prnt(' ', buf, idx++, ml);
						}
					}

					while ((*p != 0) && (!(flags & FLAGS_PRECISION) || precision--))
					{
						prnt(*(p++), buf, idx++, ml);
					}
					if (flags & FLAGS_LEFT)
					{
						while (l++ < width)
						{
							prnt(' ', buf, idx++, ml);
						}
					}
					fmt++;
					break;
				}
			case '%':
				prnt('%', buf, idx++, ml);
				fmt++;
				break;
			default:
				prnt(*fmt, buf, idx++, ml);
				fmt++;
				break;
		}
	}
	prnt((char)0, buf, idx < ml ? idx : ml - 1U, ml);
	return ((int)idx);
}
