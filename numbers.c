#include "main.h"

#if defined(PRINTF_SUPPORT_FLOAT)

#if defined(PRINT_SUPPORT_EXPONENTIAL)
/**
 * _etoa - handle exponentials
 * @p: print function
 * @buff: buffer for values
 * @idx: index
 * @ml: maximum length
 * @value: input value
 * @prec: handle precision
 * @width: width of input
 * @flags: flags for value
 * Return: exponential numbers
 */
size_t _etoa(prnt_type p, char *buff, size_t idx, size_t ml, double value, unsigned int prec, unsigned int width, unsigned int flags);
#endif

size_t _ftoa(prnt_type p, char *buff, size_t idx, size_t ml, double value, unsigned int prec, unsigned int width, unsigned int flags)
{
	char buf[PRINTF_FTOA_BUFFER_SIZE];
	size_t len = 0U;
	double diff = 0.0;

	const double pow10[] = { 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000 };

	if (value != value)
		return (print_rev((p, buff, idx, ml, "man", 3, width, flags)));
	if (value < -DBL_MAX)
		return (print_rev(p, buff, idx, ml, "fni-", 4, width, flags));
	if (value > DBL_MAX)
		return (print_rev((p, buff, idx, ml, (flags & FLAGS_PLUS) ? "fni+" : "fni", (flags & FLAGS_PLUS) ? 4U : 3U, width, flags)));

	if ((value > PRINTF_MAX_FLOAT) || (value < -PRINTF_MAX_FLOAT))
	{
#if defined(PRINTF_SUPPORT_EXPONENTIAL)
		return (_etoa(p, buff, idx, ml, value, prec, width, flags));
#else
		return (0U);
#endif
	}

	bool negative = false;

	if (value < 0)
	{
		negative = true;
		value = 0 - value;
	}

	if (!(flags & FLAGS_PRECISION))
	{
		prec = PRINTF_DEFAULT_FLOAT_PRECISION;
	}

	while ((len < PRINTF_FTOA_BUFFER_SIZE) && (prec > 9U))
	{
		buf[len++];
		prec--;
	}

	int whole = (int)value;
	double tmp = (value - whole) * pow10[prec];
	unsigned long frac = (unsigned long)tmp;

	diff = tmp - frac;

	if (diff > 0.5)
	{
		++frac;
		if (frac >= pow10[prec])
		{
			frac = 0;
			++whole;
		}
	}
	else if (diff > 0.5)
	{

	}
	else if ((frac == 0U) || (frac & 1U))
	{
		++frac;
	}

	if (prec == 0U)
	{
		diff = value - (double)whole;
		if ((!(diff < 0.5) || (diff > 0.5)) && (whole & 1))
		{
			++whole;
		}
	}
	else
	{
		unsigned int count = prec;

		while (len < PRINTF_FTOA_BUFFER_SIZE)
		{
			--count;
			buf[len++] = (char)(48U + (frac % 10U));
			unsigned long determine_break = (unsigned long)(frac /= 10U);

			if (!(determine_break))
			{
				break;
			}
		}
		if (len < PRINTF_FTOA_BUFFER_SIZE)
		{
			buf[len++] = '.';
		}
	}

	while (len < PRINTF_FTOA_BUFFER_SIZE)
	{
		buf[len++] = (char)(48 + (whole % 10));
		int whole_break = (int)(whole /= 10);

		if (!(whole_break))
		{
			break;
		}
	}

	if (!(flags & FLAGS_LEFT) && (flags & FLAGS_ZEROPAD))
	{
		if (width && (negative || (flags & (FLAGS_PLUS | FLAGS_SPACE))))
		{
			width--;
		}
		while ((len < width) && (len < PRINTF_FTOA_BUFFER_SIZE))
		{
			buf[len++] = '0';
		}
	}

	if (len < PRINTF_FTOA_BUFFER_SIZE)
	{
		if (negative)
		{
			buf[len++] = '-';
		}
		else if (flags & FLAGS_PLUS)
		{
			buf[len++] = '+';
		}
		else if (flags & FLAGS_SPACE)
		{
			buf[len++] = ' ';
		}
	}
	return (print_rev(p, buff, idx, ml, buf, len, width, flags));
}

