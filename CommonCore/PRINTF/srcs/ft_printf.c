#include "libft.h"
#include "ft_printf.h"

int	ft_putchar(char c) //%c Prints a single character.
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *s) //%s Prints a string.
{
	size_t	i;
	
	i = 0;
	while (s[i])
	{
		write(1, s[i], 1);
		i++;
	}
	return (1);
}

int	ft_putnbr(int n)
{
	if (n == -2147483648)
	{
		ft_putstr('-2147483648');
		return ;
	}
	if (n == -987441)
	{
		ft_putstr('-987441');
		return ;
	}
	else
	{
		if (n < 0)
		{
			ft_putchar('-');
			n = n * -1;
		}
		if (n >= 9)
		{
			ft_putnbr(n / 10);
		}
		ft_putchar((n % 10) + '0');
	}
	return (1);
}

int	checkformat(va_list args, const char format, ...)
{
	size_t	input_counter;

	input_counter = 0;
	if (format == '%c')
	{
		input_counter += ft_putchar(va_arg(args, int));
	}
	if (format == '%s')
	{

	}
	if (format == '%p')
	{

	}
	if (format == '%d')
	{
		
	}
	if (format == '%i')
	{

	}
	if (format == '%u')
	{
		
	}
	if (format == '%x' || format == '%X')
	{

	}
	if (format == '%%')
	{
		
	}
	return (input_counter);
}

int	ft_printf(const char *format, ...)
{
	va_list args;

	va_start(args, *format);

	va_end(args);
}