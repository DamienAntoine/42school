/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_stacks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:57:41 by dantoine          #+#    #+#             */
/*   Updated: 2024/06/07 17:19:39 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	sort_three(t_stack **astack_head, int smallest, int biggest)
{
	if ((*astack_head)->value == smallest
		&& (*astack_head)->next->value != biggest)
		return ;
	else if ((*astack_head)->value == smallest
		&& (*astack_head)->next->value == biggest)
	{
		sa(astack_head);
		ra(astack_head);
	}
	else if ((*astack_head)->value != biggest
		&& (*astack_head)->next->value == smallest)
		sa(astack_head);
	else if ((*astack_head)->value != biggest
		&& (*astack_head)->value != smallest
		&& (*astack_head)->next->value == biggest)
		rra(astack_head);
	else if ((*astack_head)->value == biggest
		&& (*astack_head)->next->value == smallest)
		ra(astack_head);
	else if ((*astack_head)->value == biggest
		&& (*astack_head)->next->value != smallest)
	{
		ra(astack_head);
		sa(astack_head);
	}
}

void	sort_four(t_stack **astack_head, t_stack **bstack_head)
{
	int	smallest;

	smallest = find_smallest(astack_head);
	put_on_top(astack_head, smallest);
	pb(astack_head, bstack_head);
	sort_three(astack_head, find_smallest(astack_head),
		find_biggest(astack_head));
	pa(astack_head, bstack_head);
}

void	insert_sorted(t_stack **astack, t_stack **bstack)
{
	t_bf	*bfnode;

	while (*bstack)
	{
		if (astack == NULL || bstack == NULL || *bstack == NULL)
			return ;
		bfnode = find_optimal_nodes(*astack, *bstack);
		if (bfnode == NULL)
			return ;
		put_on_top_both(astack, bstack, bfnode->a_node->value,
			bfnode->b_node->value);
		free(bfnode);
		pa(astack, bstack);
	}
}

void	sort_stacks(t_stack **astack_head, t_stack **bstack_head)
{
	t_stack	*astack;
	t_stack	*bstack;
	int		smallest;
	int		biggest;

	astack = *astack_head;
	bstack = *bstack_head;
	until_three(&astack, &bstack);
	smallest = find_smallest(&astack);
	biggest = find_biggest(&astack);
	sort_three(&astack, smallest, biggest);
	pa(&astack, &bstack);
	ra(&astack);
	pa(&astack, &bstack);
	ra(&astack);
	insert_sorted(&astack, &bstack);
	*astack_head = astack;
	*bstack_head = bstack;
}
