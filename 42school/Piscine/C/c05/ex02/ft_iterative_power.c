/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_power.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 11:56:42 by dantoine          #+#    #+#             */
/*   Updated: 2024/01/20 12:01:01 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_iterative_power(int nb, int power)
{
	int	result;

	result = 1;
	if (power < 0)
		return (0);
	else if (power == 0)
		return (1);
	else
	{
		while (power > 0)
		{
			result = result * nb;
			power--;
		}
	}
	return (result);
}
/*
#include <stdio.h>
int	main(void)
{
	int power = 0;
	int nb = 0;
	int result = ft_iterative_power(nb, power);

	printf("power : %d\nnumber : %d\nresult : %d", power, nb, result);
	return 0;
}
*/
