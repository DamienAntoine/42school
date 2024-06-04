/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_on_top.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:43:47 by dantoine          #+#    #+#             */
/*   Updated: 2024/06/04 12:51:43 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	put_on_top(t_stack **astack_head, int value)
{
	if (is_closer_to_top(*astack_head, value))
	{
		while ((*astack_head)->value != value)
			ra(astack_head);
	}
	else
	{
		while ((*astack_head)->value != value)
			rra(astack_head);
	}
}

void	put_on_top_bstack(t_stack **bstack_head, int value)
{
	if (is_closer_to_top(*bstack_head, value))
	{
		while ((*bstack_head)->value != value)
			rb(bstack_head);
	}
	else
	{
		while ((*bstack_head)->value != value)
			rrb(bstack_head);
	}
}

void	put_on_top_both(t_stack **astack_head, t_stack **bstack_head,
		int avalue, int bvalue)
{
	while ((*astack_head)->value != avalue || (*bstack_head)->value != bvalue)
		rotate_stacks(astack_head, bstack_head, avalue, bvalue);
}

void	rotate_stacks(t_stack **a, t_stack **b, int av, int bv)
{
	if ((*a)->value != av && (*b)->value != bv)
	{
		if (is_closer_to_top(*a, av) && is_closer_to_top(*b, bv))
			rr(a, b);
		else if (!is_closer_to_top(*a, av) && !is_closer_to_top(*b, bv))
			rrr(a, b);
		else if (is_closer_to_top(*a, av))
			ra(a);
		else
			rb(b);
	}
	else if ((*a)->value != av)
	{
		if (is_closer_to_top(*a, av))
			ra(a);
		else
			rra(a);
	}
	else if ((*b)->value != bv)
	{
		if (is_closer_to_top(*b, bv))
			rb(b);
		else
			rrb(b);
	}
}
