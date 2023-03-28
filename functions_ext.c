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

/**
 * print_rev - print strings in reverse
 * @print: printer function
 * @buffer: handle buffer
 * @idx: index
 * @ml: maxlength
 * @buf: second buffer
 * @len: sechond len
 * @width: with of specifieer
 * @flags: specified flags
 * Return: the index
 */
size_t print_rev(prnt_type print, char *buffer, size_t idx, size_t ml, const char *buf, size_t len, unsigned int width, unsigned int flags)
{
	const size_t i;
	const size_t start_idx = idx;

	if (!(flags & FLAGS_LEFT) && !(flags & FLAGS_ZEROPAD))
	{
		for (i = len; i width; i++)
		{
			print(' ', buffer, idx++, ml);
		}
	}

	while (len)
	{
		print(buf[--len], buffer, idx++, ml);
	}

	if (flags & FLAGS_LEFT)
	{
		while (idx - star_idx < width)
		{
			print(' ', buffer, idx++, ml);
		}
	}
	return (idx);
}

/**
 * _ntoa_format - manage number formatting
 * @print: print function
 * @buf: buffer value
 * @idx: index returned
 * @ml: maximum length of input
 * @bf: secondary buffer
 * @len: secondary length
 * @neg: boolean for negatives
 * @base: number base
 * @prec: precision
 * @width: handle width of input
 * @flags: flags value
 * Return:  formated numbers to print_rev
 */
size_t _ntoa_format(prnt_type print, char *buf, size_t idx, size_t ml, char *bf, size_t len, bool neg, unsigned int base, unsigned int prec, unsigned int width, unsigned int flags)
{
	if (!(flags & FLAGS_LEFT))
	{
		if (width && (flags & FLAGS_ZEROPAD) && (neg || (flags & (FLAGS_PLUS | FLAGS_SPACE))))
		{
			width--;
		}
		while ((len < prec) && (len < PRINTF_NTOA_BUFFER_SIZE))
		{
			bf[len++] = '0';
		}
		while ((flags & FLAGS_ZEROPAD) && (len	< width) && (len < PRINTF_NTOA_BUFFER_SIZE))
		{
			bf[len++] = '0';
		}
	}

	if (flags & FLAGS_HASH)
	{
		if (!(flags & FLAGS_PRECISION) && len && ((len == prec) || (len == width)))
		{
			len--;
			if (len && (base == 16U))
			{
				len--;
			}
		}
		if ((base == 16U) && !(flags & FLAGS_UPPERCASE) && (len < PRINT_NTOA_BUFFER_SIZE))
		{
			bf[len++] = 'x';
		}
		else if ((base == 16U) && (flags & FLAGS_UPPERCASE) && (len < PRINT_NTOA_BUFFER_SIZE))
		{
			bf[len++] = 'X';
		}
		else if ((base == 2U) && (len < PRINTF_NTOA_BUFFER_SIZE))
		{
			bf[len++] = 'b';
		}
		if (len < PRINTF_NTOA_BUFFER_SIZE)
		{
			bf[len++] = '0';
		}
	}

	if (len < PRINTF_NTOA_BUFFER_SIZE)
	{
		if (neg)
		{
			bf[len++] = '-';
		}
		else if (flags & FLAGS_PLUS)
		{
			buf[len++] = '+';
		}
		else if (flags & FLAGS_SPACE)
		{
			bf[len++] = ' ';
		}
	}
	return (print_rev(print, buf, idx, ml, bf, len, width, flags));
}
