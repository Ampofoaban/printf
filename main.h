#ifndef MAIN_H
#define MAIN_H
#include <stdarg.h>


/* FLAGS */
#define F_MINUS 1
#define F_PLUS 2
#define F_ZERO 4
#define F_HASH 8
#define F_SPACE 16

/* SIZES */
#define S_LONG 2
#define S_SHORT 1

/**
 * struct fmt - Struct op
 *
 * @fmt: The format.
 * @fn: The function associated.
 */

/**
 * typedef struct fmt fmt_t - Struct op
 *
 * @fmt: The format.
 * @fm_t: The function associated.
 */

int _putchar(char c);
int _printf(const char *format, va_list va);
int handle_print(const char *fmt);
int handle_string_printing(char *str);
int _printfsub(const char *format, va_list va);
/****************** FUNCTIONS ******************/

/* Funtions to print chars and strings */

/* Functions to print numbers */
#endif /* MAIN_H */
