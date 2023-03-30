#include "main.h"

/**
 * print_pad - handle padding of strings
 * @prnt: print function
 * @buf: buffer val
 * @idx: index
 * @ml: maximum length
 * @padchar: char to pad
 * @c: count value
 * Return: idx value
 */
size_t print_pad(prnt_type prnt, char *buf, size_t idx, size_t ml, char padchar, int c)
{
	while (c-- > 0)
	{
		prnt(padchar, buf, idx++, ml);
	}
	return (idx);
}

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

	const int pad = width - len;

	if (!(flags & FLAGS_LEFT) && !(flags & FLAGS_ZEROPAD))
	{
		idx = print_pad(print, buffer, idx, ml, ' ', pad);
	}

	while (len)
	{
		print(buf[--len], buffer, idx++, ml);
	}

	if (flags & FLAGS_LEFT)
	{
		idx = print_pad(print, buffer, idx, ml, ' ', pad);
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
		if ((base == 16U) && !(flags & FLAGS_UPPERCASE) && (len < PRINTF_NTOA_BUFFER_SIZE))
		{
			bf[len++] = 'x';
		}
		else if ((base == 16U) && (flags & FLAGS_UPPERCASE) && (len < PRINTF_NTOA_BUFFER_SIZE))
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

/**
 * _ntoa_long - handle long numbers
 * @p: print function
 * @buf: buffer
 * @idx: index
 * @ml: maximum length
 * @value: parsed value
 * @neg: boolean for negatives
 * @base: number base
 * @prec: precision
 * @width: width of parameters
 * @flags: added flags
 * Return: formatted long numbers
 */
size_t _ntoa_long(prnt_type p, char *buf, size_t idx, size_t ml, unsigned long value, bool neg, unsigned long base, unsigned int prec, unsigned int width, unsigned int flags)
{
	char bf[PRINTF_NTOA_BUFFER_SIZE];
	size_t len = 0U;

	if (!value)
	{
		flags &= ~FLAGS_HASH;
	}

	if (!(flags & FLAGS_PRECISION) || value)
	{
		do {
			const char digit = (char)(value % base);

			bf[len++] = digit < 10 ? '0' + digit : (flags & FLAGS_UPPERCASE ? 'A' : 'a') + digit - 10;
			value /= base;
		} while (value && (len < PRINTF_NTOA_BUFFER_SIZE));
	}

	return (_ntoa_format(p, buf, idx, ml, bf, len, neg, (unsigned int)base, prec, width, flags));
}
/*
#if defined(PRINTF_SUPPORT_LONG_LONG)

 * _ntoa_long_long - format long long numbers
 * @p: print type
 * @buff: buffer for characters
 * @idx: index value
 * @ml: maximum length
 * @value: parsed value
 * @neg: boolean for negatvies
 * @base: number base
 * @prec: hancle precision
 * @width: width of input
 * @flags: flags for formatting
 * Return: formatted long long numbers
 *
size_t _ntoa_long_long(prnt_type p, char *buff, size_t idx, size_t ml, unsigned long long value, bool neg, unsigned long long base, unsigned int prec, unsigned int width, unsigned int flags)
{
	char buf[PRINTF_NTOA_BUFFER_SIZE];
	size_t len = 0U;

	if (!value)
	{
		flags &= ~FLAGS_HASH;
	}

	if (!(flags & FLAGS_PRECISION) || value)
	{
		do {
			const char digit = (char)(value % base);

			buf[len++] = digit < 10 ? '0' + digit : (flags & FLAGS_UPPERCASE ? 'A' : 'a') + digit - 10;
			value /= base;
		} while (value && (len < PRINTF_NTOA_BUFFER_SIZE));
	}
	return (_ntoa_format(p, buff, idx, ml, buf, len, neg, (unsigned int)base, prec, width, flags));
}
#endif
*/
