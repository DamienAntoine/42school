/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_stacks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:21:51 by dantoine          #+#    #+#             */
/*   Updated: 2024/06/04 12:50:47 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	free_stack(t_stack *a_stack)
{
    t_stack *temp;

    while (a_stack)
    {
        temp = a_stack;
        a_stack = a_stack->next;
        free(temp);
    }
}

void	free_moves(t_moves **moves)
{
	t_moves	*temp;

	while (moves)
	{
		temp = (*moves)->next;
		free(moves);
		*moves = temp;
	}
}

long	ft_atol(const char *str)
{
	long	sign;
	long	result;
	long	i;

	sign = 1;
	result = 0;
	i = 0;
	while ((str[i] == 32) || (str[i] >= 9 && str[i] <= 13))
	{
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
		{
			sign *= -1;
		}
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (sign * result);
}
