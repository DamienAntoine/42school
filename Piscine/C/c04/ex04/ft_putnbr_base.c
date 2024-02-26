/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 11:52:09 by dantoine          #+#    #+#             */
/*   Updated: 2024/01/20 18:57:29 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int	checkbase(char *base)
{
	int	i;
	int	j;

	i = 0;
	while (base[i] != '\0')
	{
		if (base[i] == '-' || base[i] == '+' || base[i] == base[i + 1])
			return (0);
		j = i + 1;
		while (base[j] != '\0')
		{
			if (base[i] == base[j])
				return (0);
			j++;
		}
		i++;
	}
	if (i <= 1)
		return (0);
	return (1);
}

void	print_base_nbr(int nbr, char *base, int size)
{
	char	a;
	int		n;

	if (nbr < 0)
	{
		write(1, "-", 1);
		n = nbr * (-1);
	}
	else
		n = nbr;
	if (n >= size)
	{
		print_base_nbr(n / size, base, size);
		a = base[n % size];
		write(1, &a, 1);
	}
}

void	ft_putnbr_base(int nb, char *base)
{
	int	s;

	s = 0;
	if (checkbase(base) == 1)
	{
		while (base[s] != 0)
			s++;
		print_base_nbr(nb, base, s);
	}
}
/*
int	main(void)
{
	int	number1 = 123;
	char	base1[] = "0123456789";
	ft_putnbr_base(number1, base1);
	ft_putchar('\n');

	int     number2 = -1010;
        char    base2[] = "01";
        ft_putnbr_base(number2, base2);
        ft_putchar('\n');

	int     number3 = 255;
        char    base3[] = "0123456789ABCDEF";
        ft_putnbr_base(number3, base3);
        ft_putchar('\n');

	int     number4 = 42;
        char    base4[] = "012++345";
        ft_putnbr_base(number4, base4);
        ft_putchar('\n');

	return (0);
}
*/
