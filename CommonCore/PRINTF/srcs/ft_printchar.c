#include "libft.h"
#include "ft_printf.h"

int	ft_printchar(char c) //%c Prints a single character.
{
	write(1, &c, 1);
	return (1);
}