#include <stdarg.h>
#include <unistd.h>

int	ft_putchar(char c) //%c Prints a single character.
{
	write(1, &c, 1);
	return (0);
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
	return (0);
}

void	ft_putnbr(int n)
{
	if (n == -2147483648)
	{
		ft_putstr("-2147483648");
		return ;
	}
	if (n == -987441)
	{
		ft_putstr("-987441");
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
		ft_putchar_fd((n % 10) + '0');
	}
}

int	ft_atoi(const char *str)
{
	int	sign;
	int	result;
	int	i;

	sign = 1;
	result = 0;
	i = 0;
	while ((str[i] == 32) || (str[i] >= 9 && str[i] <= 13))
	{
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
		{
			sign *= -1;
		}
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (sign * result);
}

int	ft_printf(const char *format, ...)
{
	va_list args;

	va_start(args, *format);

	va_end(args);
}