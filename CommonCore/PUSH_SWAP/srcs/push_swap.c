/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:30:08 by dantoine          #+#    #+#             */
/*   Updated: 2024/06/04 12:30:40 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	until_five(t_stack **astack_head, t_stack **bstack_head)
{
	int	counter;
	t_stack	*astack;
	int	mean;

	counter = 0;
	astack = *astack_head;
	while (astack)
	{
		counter++;
		astack = astack->next;
	}
	while (counter > 5)
	{
		mean = find_mean_value(astack_head);
		if ((*astack_head)->value > mean)
			untilfive_helper(astack_head);
		else if ((*astack_head)->value <= mean)
		{
			pb(astack_head, bstack_head);
			counter--;
		}
	}
}

void	untilfive_helper(t_stack **astack_head)
{
	int	target;

	target = (*astack_head)->value;
	if (is_closer_to_top(*astack_head, target))
		ra(astack_head);
	else
		rra(astack_head);
}
