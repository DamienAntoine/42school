/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_costs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:33:07 by dantoine          #+#    #+#             */
/*   Updated: 2024/06/04 12:34:14 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

t_stack	*to_last_node(t_stack *stack)
{
	if (stack == NULL)
		return (NULL);
	while (stack->next != NULL)
	{
		stack = stack->next;
	}
	return (stack);
}

int	cost_to_top(t_stack *stack_head, int value)
{
	int	cost;
	int	reverse_cost;
	int	size;
	t_stack	*node;

	cost = 0;
	node = stack_head;
	while (node != NULL && node->value != value)
	{
		cost++;
		node = node->next;
	}
	size = 0;
	node = stack_head;
	while (node != NULL)
	{
		size++;
		node = node->next;
	}
	reverse_cost = size - cost;
	if (cost < reverse_cost)
		return (cost);
	else
		return (reverse_cost);
}


int		is_closer_to_top(t_stack *bstack_head, int value)
{
	t_stack *temp;
	int	i;
	int	index_temp;

	temp = bstack_head;
	i = 0;
	if (temp->value == value)
		return (-1);
	while (temp)
	{
		i++;
		temp->index = i;
		if (temp->value == value)
			index_temp = i;
		temp = temp->next;
	}
	if (index_temp <= ((i / 2) + 1))
		return (1);
	else
		return (0);
}
