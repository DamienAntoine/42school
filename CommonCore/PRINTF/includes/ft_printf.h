#ifndef FT_PRINTF_H
# define FT_PRINTF_H
#include <stdarg.h>
#include <unistd.h>
# include "libft.h"

int	ft_putchar(char c);
int	ft_putstr(char *s);
int	ft_putnbr(int n);
float	ft_putdecimal(float n);
#endif