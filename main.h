#ifndef MAIN_H
#define MAIN_H
#include <stdarg.h>
#include <stddef.h>

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

typedef void (*prnt_type)(char character, void *buffer, size_t idx, size_t maxlen);

int _putchar(char c);
int _printf(const char *format, ...);
void handle_print(char fmt, void * buffer, size_t idx, size_t maxlen);
int handle_string_printing(char *str);
int _vprintf(prnt_type print, char *buffer, size_t maxlen, const char *format, va_list va);
/****************** FUNCTIONS ******************/

/* Funtions to print chars and strings */

/* Functions to print numbers */
#endif /* MAIN_H */
