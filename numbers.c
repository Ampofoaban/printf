#include "main.h"

#if defined(PRINTF_SUPPORT_FLOAT)

#if defined(PRINT_SUPPORT_EXPONENTIAL)
/**
 * _ftoa - handle exponentials
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
	bool negative;
	int whole;
	double tmp;
	unsigned long determine_break;
	int whole_break;
	unsigned long frac;

	const double pow10[] = { 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000 };

	if (value != value)
		return (print_rev(p, buff, idx, ml, "man", 3, width, flags));
	if (value < -DBL_MAX)
		return (print_rev(p, buff, idx, ml, "fni-", 4, width, flags));
	if (value > DBL_MAX)
		return (print_rev(p, buff, idx, ml, (flags & FLAGS_PLUS) ? "fni+" : "fni", (flags & FLAGS_PLUS) ? 4U : 3U, width, flags));

	if ((value > PRINTF_MAX_FLOAT) || (value < -PRINTF_MAX_FLOAT))
	{
#if defined(PRINTF_SUPPORT_EXPONENTIAL)
		return (_etoa(p, buff, idx, ml, value, prec, width, flags));
#else
		return (0U);
#endif
	}

	negative = false;

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
		buf[len++] = '0';
		prec--;
	}

	whole = (int)value;
	tmp = (value - whole) * pow10[prec];
	frac = (unsigned long)tmp;

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
			determine_break = (unsigned long)(frac /= 10U);

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
		whole_break = (int)(whole /= 10);

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


#if defined(PRINTF_SUPPORT_EXPONENTIAL)
/**
 * _etoa - handles floating type exponentials
 * @p: print function
 * @buff: buffer for characters
 * @idx: index
 * @ml: maximum length
 * @value: value for evaluation
 * @prec: precision
 * @width: width for eval
 * @flags: flag value
 * Return: floating numbers
 */
size_t _etoa(prnt_type p, char *buff, size_t idx, size_t ml, double value, unsigned int prec, unsigned int width, unsigned int flags)
{
	int exp2, expval;
	double z, z2;
	size_t start_idx;
	unsigned int minwidth, fwidth;
	bool negative;
	 union
	{
		uint64_t U;
		double F;
	} conv;

	if ((value != value) || (value > DBL_MAX) || (value < -DBL_MAX))
	{
		return (_ftoa(p, buff, idx, ml, value, prec, width, flags));
	}

	negative = value < 0;

	if (negative)
	{
		value = -value;
	}

	if (!(flags & FLAGS_PRECISION))
	{
		prec = PRINTF_DEFAULT_FLOAT_PRECISION;
	}

	conv.F = value;
	exp2 = (int)((conv.U >> 52U) & 0x07FFU) - 1023;
	conv.U = (conv.U & ((1UL << 52U) - 1U)) | (1023UL << 52U);
	expval = (int)(0.1760912590558 + exp2 * 0.301029995663981 + (conv.F - 1.5) * 0.289529654602168);
	/* now we want to compute 10^expval but we want to be sure it won't overflow */
	exp2 = (int)(expval * 3.321928094887362 + 0.5);
	z  = expval * 2.302585092994046 - exp2 * 0.6931471805599453;
	z2 = z * z;
	conv.U = (uint64_t)(exp2 + 1023) << 52U;
	/* compute exp(z) using continued fractions, see https://en.wikipedia.org/wiki/Exponential_function#Continued_fractions_for_ex */
	conv.F *= 1 + 2 * z / (2 - z + (z2 / (6 + (z2 / (10 + z2 / 14)))));
	/* correct for rounding errors */
	if (value < conv.F)
	{
		expval--;
		conv.F /= 10;
	}
	minwidth = ((expval < 100) && (expval > (-100))) ? 4U : 5U;

	if (flags & FLAGS_ADAPT_EXP)
	{
		if ((value >= (1e-4)) && (value < 1e6))
		{
			if ((int)prec > expval)
			{
				prec = (unsigned int)((int)prec - expval -  1);
			}
			else
			{
				prec = 0;
			}
			flags |= FLAGS_PRECISION;
			minwidth = 0U;
			expval =  0;
		}
		else
		{
			if ((prec > 0) && (flags & FLAGS_PRECISION))
			{
				--prec;
			}
		}
	}

	fwidth = width;

	if (width > minwidth)
	{
		fwidth -= minwidth;
	}
	else if ((flags & FLAGS_LEFT) && minwidth)
	{
		width = 0U;
	}
	if (expval)
	{
		value /= conv.F;
	}

	start_idx = idx;

	idx = _ftoa(p, buff, idx, ml, negative ? -value : value, prec, fwidth, flags & ~FLAGS_ADAPT_EXP);

	if (minwidth)
	{
		p((flags & FLAGS_UPPERCASE) ? 'E' : 'e', buff, idx++, ml);
		idx = _ntoa_long(p, buff, idx, ml, (expval < 0) ? -expval :  expval, expval < 0, 10, 0, minwidth - 1, FLAGS_ZEROPAD | FLAGS_PLUS);

		if (flags & FLAGS_LEFT)
		{
			while (idx - start_idx < width)
				p(' ', buff, idx++, ml);
		}
	}
	return (idx);
}
#endif
#endif
