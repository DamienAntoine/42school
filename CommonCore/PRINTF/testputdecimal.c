#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	while (*str != '\0')
	{
		write(1, str, 1);
		str++;
	}
}

int	ft_putdecimal(float n)
{
	char digits[10];
	int	i;

	i = 0;
	if (n < 0)
	{
		ft_putchar('-');
		n = n * -1;
	}
	if (n == 0)
		ft_putchar('0');
	if (n >= 9)
		{
			ft_putdecimal(n / 10);
		}
	ft_putchar((n % 10) + '0');

	while (n > 0)
	{
		digits[i++] = '0' + (n % 10);
		n /= 10;
	}
	while (--i >= 0)
	{
		if (digits[i] == ',')
			ft_putchar(',');
		ft_putchar(digits[i]);
	}
	return (1);
}

int main()
{
	int	decimal = 123.456;
	ft_putdecimal(decimal);
	return 0;
}