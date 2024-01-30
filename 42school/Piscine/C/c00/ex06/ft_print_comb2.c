/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_comb2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <dantoine@student.42luxembourg.lu>+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 17:07:49 by dantoine          #+#    #+#             */
/*   Updated: 2024/01/25 16:21:38 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putstr(char *str)
{
	while (*str != '\0')
	{
		write(1, str, 1);
		str++;
	}
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_print_comb2(void)
{
	int	a;
	int	b;
	int	first_iteration;

	a = 00;
	b = 01;
	first_iteration = 1;
	while (a <= 98)
	{
		while (b <= 99)
		{
			ft_putchar(a / 10 + '0');
			ft_putchar(a % 10 + '0');
			ft_putchar(' ');
			ft_putchar(b / 10 + '0');
			ft_putchar(b % 10 + '0');
			if (!first_iteration || (a != 98 || b != 99))
				ft_putstr(", ");
			first_iteration = 0;
			b++;
		}
		a++;
		b = a + 1;
		first_iteration = 1;
	}
}
/*
int	main(void)
{
	ft_print_comb2();
	return (0);
}
*/
