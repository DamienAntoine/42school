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
	t_stack	*temp;

	while (a_stack)
	{
		temp = a_stack->next;
		free(a_stack);
		a_stack = temp;
	}
	free(a_stack);
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
	free(moves);
}
