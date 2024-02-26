/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_factorial.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 11:18:39 by dantoine          #+#    #+#             */
/*   Updated: 2024/01/21 16:13:13 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_iterative_factorial(int nb)
{
	int	i;
	int	result;

	i = 1;
	result = (1);
	if (nb == 0)
		return (1);
	else if (nb < 0)
		return (0);
	while (i <= nb)
	{
		result = result * i;
		i++;
	}
	return (result);
}
/*
#include <stdio.h>
int	main(void)
{
	int number = 3;
	int result = ft_iterative_factorial(number);

	if (result >= 0)
		printf("Factorial of %d is : %d\n", number, result);
	else
		printf("incorrect input");
	return (0);
}
*/
