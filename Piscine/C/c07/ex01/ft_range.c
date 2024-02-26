/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:03:11 by dantoine          #+#    #+#             */
/*   Updated: 2024/01/24 14:22:19 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	*ft_range(int min, int max)
{
	int	i;
	int	array_size;
	int	*array;

	i = 0;
	array_size = (max - min);
	array = (int *)malloc(array_size * sizeof(int));
	if (min >= max)
		return (0);
	while (i < array_size)
	{
		array[i] = min + i;
		i++;
	}
	return (array);
}
/*
#include <stdio.h>
int	main(void)
{
	int	*result;
	int	i;
	int	arraysize;
	int	min;
	int	max;

	min = 10;
	max = 15;
	arraysize = max - min;
	i = 0;
	result = ft_range(min, max);
	while (i < arraysize)
	{
		printf("%d", result[i]);
		if (i < arraysize - 1)
			printf(", ");
		i++;
	}
	free (result);
	return (0);
}
*/
