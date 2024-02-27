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