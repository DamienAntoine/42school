/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_on_top.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:36:04 by dantoine          #+#    #+#             */
/*   Updated: 2024/06/04 15:36:05 by dantoine         ###   ########.fr       */
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

void	put_on_top_both(t_stack **a, t_stack **b, int av, int bv)
{
	while ((*a)->value != av || (*b)->value != bv)
		rotate_stacks(a, b, av, bv);
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
