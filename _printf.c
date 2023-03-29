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
	bool is_ll;
	unsigned int n, width, precision, flags;

	if (!buf)
	{
		prnt = print_null;
	}

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
			const int w = va_arg(va, int);

			if (w < 0)
			{
				flags |= FLAGS_LEFT;
				width = (unsigned int)-w;
			}
			else
			{
				width = (unsigned int)w;
			}
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
			case 'l':
				flags |= FLAGS_LONG;
				fmt++;
				if (*fmt == 'l')
				{
					flags |= FLAGS_LONG_LONG;
					fmt++;
				}
				break;
			case 'h':
				flags |= FLAGS_SHORT;
				fmt++;
				if (*fmt == 'h')
				{
					flags |= FLAGS_CHAR;
					fmt++;
				}
				break;
#if defined(PRINTF_SUPPORT_PTRDIFF_T)
			case 't':
				flags |= (sizeof(ptrdiff_t) == sizeof(long) ? FLAGS_LONG : FLAGS_LONG_LONG);
				fmt++;
				break;
#endif
			case 'j':
				flags |= (sizeof(intmax_t) == sizeof(long) ? FLAGS_LONG : FLAGS_LONG_LONG);
				fmt++;
				break;
			case 'z':
				flags |= (sizeof(size_t) == sizeof(long) ? FLAGS_LONG : FLAGS_LONG_LONG);
				fmt++;
				break;
			default:
				break;
		}

		switch (*fmt)
		{
			case 'd':
			case 'i':
			case 'u':
			case 'x':
			case 'X':
			case 'o':
			case 'b':
				{
					unsigned int base;

					if (*fmt == 'x' || *fmt == 'X')
					{
						base = 16U;
					}
					else if (*fmt == 'o')
					{
						base = 8U;
					}
					else if (*fmt == 'b')
					{
						base = 2U;
					}
					else
					{
						base = 10U;
						flags &= ~FLAGS_HASH;
					}

					if (*fmt == 'X')
					{
						flags |= FLAGS_UPPERCASE;
					}

					if ((*fmt != 'i') && (*fmt != 'd'))
					{
						flags &= ~(FLAGS_PLUS | FLAGS_SPACE);
					}

					if (flags & FLAGS_PRECISION)
					{
						flags &= ~FLAGS_ZEROPAD;
					}

					if ((*fmt == 'i') || (*fmt == 'd'))
					{
						if (flags & FLAGS_LONG_LONG)
						{
#if defined(PRINTF_SUPPORT_LONG_LONG)
							const long value = va_arg(va, long);
							idx = _ntoa_long(prnt, buf, idx, ml, (unsigned long)(value > 0 ? value : 0 - value), value < 0, base, precision, width, flags);
#endif
						}
						else if (flags & FLAGS_LONG)
						{
							const long value = va_arg(va, long);
							idx = _ntoa_long(prnt, buf, idx, ml, (unsigned long)(value > 0 ? value : 0 - value), value < 0,  base, precision, width, flags);
						}
						else
						{
							const int value = (flags & FLAGS_CHAR) ? (char)va_arg(va, int) : (flags & FLAGS_SHORT) ? (short int)va_arg(va, int) : va_arg(va, int);
							idx = _ntoa_long(prnt, buf, idx, ml, (unsigned int)(value > 0 ? value : 0 - value), value < 0, base, precision, width, flags);
						}
					}
					else
					{
						if (flags & FLAGS_LONG_LONG)
						{
#if defined(PRINTF_SUPPORT_LONG_LONG)
							idx = _ntoa_long(prnt, buf, idx, ml, va_arg(va, unsigned long), false, base, precision, width, flags);
#endif
						}
						else if (flags & FLAGS_LONG)
						{
							idx = _ntoa_long(prnt, buf, idx, ml, va_arg(va, unsigned long), false, base, precision, width, flags);
						}
						else
						{
						const unsigned int value = (flags & FLAGS_CHAR) ? (unsigned char)va_arg(va, unsigned int) : (flags & FLAGS_SHORT) ? (unsigned short int)va_arg(va, unsigned int) : va_arg(va, unsigned int);
					idx = _ntoa_long(prnt, buf, idx, ml, value, false, base, precision, width, flags);
						}
					}
					fmt++;
					break;
				}
#if defined(PRINTF_SUPPORT_FLOAT)
			case 'f':
			case 'F':
				if (*fmt == 'F')
				{
					flags |= FLAGS_UPPERCASE;
				}
				idx = _ftoa(prnt, buf, idx, ml, va_arg(va, double), precision, width, flags);
				fmt++;
				break;
#if defined(PRINTF_SUPPORT_EXPONENTIAL)
			case 'e':
			case 'E':
			case 'g':
			case 'G':
				if ((*fmt == 'g')||(*fmt == 'G'))
				{
					flags |= FLAGS_ADAPT_EXP;
				}
				if ((*fmt == 'E')||(*fmt == 'G'))
				{
					flags |= FLAGS_UPPERCASE;
				}
				idx = _etoa(prnt, buf, idx, ml, va_arg(va, double), precision, width, flags);
				fmt++;
				break;
#endif
#endif
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
			case 'p':
				{
					width = sizeof(void *) * 2U;
					flags = FLAGS_ZEROPAD | FLAGS_UPPERCASE;
#if defined(PRINTF_SUPPORT_LONG_LONG)
					is_ll = sizeof(uintptr_t) == sizeof(long);
					if(is_ll)
					{
						idx = _ntoa_long(prnt, buf, idx, ml, (uintptr_t)va_arg(va, void*), false, 16U, precision, width, flags);
				}
					else
					{
#endif
						idx = _ntoa_long(prnt, buf, idx, ml, (unsigned long)((uintptr_t)va_arg(va, void*)), false, 16U, precision, width, flags);
#if defined(PRINTF_SUPPORT_LONG_LONG)
					}
#endif
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
