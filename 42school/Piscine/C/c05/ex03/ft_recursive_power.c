/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursive_power.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 11:23:11 by dantoine          #+#    #+#             */
/*   Updated: 2024/01/21 16:14:33 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_recursive_power(int nb, int power)
{
	int	result;

	result = 1;
	if (power < 0)
		return (0);
	else if (power == 0)
		return (1);
	else
		result = nb * ft_recursive_power(nb, power - 1);
	return (result);
}
/*
#include <stdio.h>
int	main(void)
{
	int power = 10;
	int nb = 5;
	int result = ft_recursive_power(nb, power);

	printf("power : %d\nnumber : %d\nresult : %d", power, nb, result);
	return 0;
}
*/
