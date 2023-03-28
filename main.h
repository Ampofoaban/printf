#ifndef MAIN_H
#define MAIN_H
#include <stdarg.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>

/* FLAGS */
#define FLAGS_ZEROPAD (1U << 0U)
#define FLAGS_LEFT (1U << 1U)
#define FLAGS_PLUS (1U << 2U)
#define FLAGS_SPACE (1U << 3U)
#define FLAGS_HASH (1U << 4U)
#define FLAGS_UPPERCASE (1U << 5U)
#define FLAGS_CHAR (1U << 6U)
#define FLAGS_SHORT (1U << 7U)
#define FLAGS_LONG      (1U <<  8U)
#define FLAGS_LONG_LONG (1U <<  9U)
#define FLAGS_PRECISION (1U << 10U)
#define FLAGS_ADAPT_EXP (1U << 11U)

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
bool _is_digit(char ch);
unsigned int _strnlen_s(const char* str, size_t maxsize);
unsigned int _atoi(const char **str);
int _vprintf(prnt_type print, char *buffer, size_t maxlen, const char *format, va_list va);
/****************** FUNCTIONS ******************/

/* Funtions to print chars and strings */
void h_c(prnt_type print, char * buffer, size_t maxlength, size_t idx, const char *format, va_list va);
/* Functions to print numbers */
#endif /* MAIN_H */
