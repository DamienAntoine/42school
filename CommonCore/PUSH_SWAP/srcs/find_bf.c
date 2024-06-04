/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_bf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:35:09 by dantoine          #+#    #+#             */
/*   Updated: 2024/06/04 15:35:11 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

t_bf	*find_optimal_nodes(t_stack *astack_head, t_stack *bstack_head)
{
	t_bf	*pairs;
	t_bf	*optimal;
	t_bf	*result;

	pairs = find_pairs(astack_head, bstack_head);
	optimal = find_smaller_cost(pairs, astack_head, bstack_head);
	result = NULL;
	if (optimal)
	{
		result = (t_bf *)malloc(sizeof(t_bf));
		if (!result)
			return (NULL);
		*result = *optimal;
		result->next = NULL;
	}
	free_pairs(pairs);
	return (result);
}

void	free_pairs(t_bf *pairs)
{
	t_bf	*tmp;

	while (pairs)
	{
		tmp = pairs;
		pairs = pairs->next;
		free(tmp);
	}
}

t_bf	*find_smaller_cost(t_bf *optimal, t_stack *astack, t_stack *bstack)
{
	t_bf	*best_cost;
	t_bf	*current;

	best_cost = optimal;
	current = optimal;
	if (optimal == NULL)
		return (NULL);
	best_cost->cost = cost_to_top(astack, current->a_node->value)
		+ cost_to_top(bstack, current->b_node->value);
	current = current->next;
	while (current)
	{
		current->cost = cost_to_top(astack, current->a_node->value)
			+ cost_to_top(bstack, current->b_node->value);
		if (current->cost < best_cost->cost)
			best_cost = current;
		current = current->next;
	}
	return (best_cost);
}
