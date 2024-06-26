/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:54:30 by dantoine          #+#    #+#             */
/*   Updated: 2024/06/04 12:54:35 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	push(t_stack **src_head, t_stack **dest_head)
{
	t_stack	*temp;

	if (*src_head == NULL)
		return ;
	temp = *src_head;
	*src_head = (*src_head)->next;
	temp->next = *dest_head;
	*dest_head = temp;
}

void	pa(t_stack **astack, t_stack **bstack)
{
	if (!*bstack)
		return ;
	push(bstack, astack);
	store_op(10);
}

void	pb(t_stack **astack, t_stack **bstack)
{
	if (!*astack)
		return ;
	push(astack, bstack);
	store_op(11);
}
