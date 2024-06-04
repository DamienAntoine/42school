/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:52:46 by dantoine          #+#    #+#             */
/*   Updated: 2024/06/04 14:53:03 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	check_stack(t_stack **stack_head)
{
	t_stack	*temp;
	t_stack	*current;

	current = *stack_head;
	while (current)
	{
		temp = current;
		while (temp->next)
		{
			temp = temp->next;
			if (temp->value == current->value)
				return (1);
		}
		current = current->next;
	}
	return (0);
}
