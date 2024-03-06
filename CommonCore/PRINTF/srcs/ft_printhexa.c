#include "../includes/ft_printf.h"

int	ft_hexalen(unsigned	int nb)
{
	int	len;

	len = 0;
	while (nb != 0)
	{
		len++;
		nb = nb / 16;
	}
	return (len);
}

void	ft_puthexa(unsigned int nb, const char spec)
{
	if (nb >= 16)
	{
		ft_puthexa(nb / 16, spec);
		ft_puthexa(nb % 16, spec);
	}
	else
	{
		if (nb <= 9)
			ft_printchar(nb + '0');
		else
		{
			if (spec == 'x')
				ft_printchar(nb - 10 + 'a');
			if (spec == 'X')
				ft_printchar(nb - 10 + 'A');
		}
	}
}

int	ft_printhexa(unsigned int nb, const char spec)
{
	if (nb == 0)
		return (write(1, "0", 1));
	else
		ft_puthexa(nb, spec);
	return (ft_hexalen(nb));
}