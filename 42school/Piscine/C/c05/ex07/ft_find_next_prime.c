/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_next_prime.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:06:00 by dantoine          #+#    #+#             */
/*   Updated: 2024/01/29 16:06:28 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_is_prime(int nb)
{
	int	i;

	i = 2;
	if (nb < 2)
		return (0);
	while (i <= nb / i)
	{
		if (nb % i == 0)
			return (0);
		i++;
	}
	return (1);
}

int	ft_find_next_prime(int nb)
{
	if (nb < 2147483647)
	{
		while (ft_is_prime(nb) != 1)
		{
			ft_is_prime(nb++);
		}
	}
	return (nb);
}
#include <stdio.h>
int	main(void)
{
	int	nb;

	nb = -54;
	if (ft_is_prime(nb) == 1)
		printf("%d is a prime number\n", nb);
	else
		printf("%d is not a prime number\n", nb);
	nb = ft_find_next_prime(nb);
	printf("Next prime number is %d", nb);
	return (0);
}
