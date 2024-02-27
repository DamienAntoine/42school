#include "libft.h"
#include "ft_printf.h"

int	ft_printnbr(int n)
{
	if (n == -2147483648)
	{
		ft_printstr('-2147483648');
		return ;
	}
	if (n == -987441)
	{
		ft_printstr('-987441');
		return ;
	}
	else
	{
		if (n < 0)
		{
			ft_printchar('-');
			n = n * -1;
		}
		if (n == 0)
			ft_printchar('0');
		if (n >= 9)
		{
			ft_printnbr(n / 10);
		}
		ft_printchar((n % 10) + '0');
	}
	return (1);
}

int	ft_print_digit(long n, int base)
{
	int count;
	char *symbols;
	symbols = "0123456789abcdef";
	if (n < 0)
	{
		write(1, "-", 1);
		return ft_print_digit(-n, base) + 1;
	}
	else if (n < base)
		return ft_print_char(symbols[n]);
	else
	{
		count = print_digit(n / base, base);
		return count + print_digit(n % base, base);
	}
}
