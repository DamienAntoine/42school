/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultimate_range.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 14:02:58 by dantoine          #+#    #+#             */
/*   Updated: 2024/01/24 14:41:03 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_ultimate_range(int **range, int min, int max)
{
	int	array_size;
	int	*array;
	int	i;

	i = 0;
	if (min >= max)
	{
		*range = NULL;
		return (0);
	}
	array_size = max - min;
	array = (int *) malloc (array_size * sizeof(int));
	if (array == NULL)
	{
		*range = NULL;
		return (-1);
	}
	while (i < array_size)
	{
		array[i] = min + i;
		i++;
	}
	*range = array;
	return (array_size);
}
/*
#include <stdio.h>
int	main(void)
{
	int	*result;
	int	i;
	int	min;
	int	max;
	int	arraysize;

	min = -5;
	max = 15;
	result = NULL;
	arraysize = ft_ultimate_range(&result, min, max);

	if (result != NULL)
	{
		i = 0;
		printf("Array : ");
		while (i < arraysize)
		{
			printf("%d", result[i]);
			if (i < arraysize - 1)
				printf(", ");
			i++;
		}
		printf("\nSize of range : %d", arraysize);

		free(result);
	}
	else
	{
		printf("Allocation failed.\n");
	}
	return (0);
}
*/
