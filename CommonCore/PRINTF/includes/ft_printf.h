#ifndef FT_PRINTF_H
# define FT_PRINTF_H
#include <stdarg.h>
#include <unistd.h>
#include <stdint.h>
# include "libft.h"

int	ft_printchar(char c);
int	checkformat(const char specifier, va_list ap);
int	ft_printf(const char *format, ...);
int	ft_print_digit(long n, int base, char spec);
int	ft_printstr(char *s);
int ft_printunsigned(unsigned int nb);
int	ft_printvoid(uintptr_t *ptr);
#endif