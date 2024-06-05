/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:55:42 by dantoine          #+#    #+#             */
/*   Updated: 2024/06/04 12:56:24 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	reverse_rotate(t_stack **head)
{
	t_stack	*temp;
	t_stack	*last_node;
	t_stack	*prev_node;

	prev_node = NULL;
	if (*head == NULL || (*head)->next == NULL)
		return ;
	last_node = *head;
	while (last_node->next)
	{
		prev_node = last_node;
		last_node = last_node->next;
	}
	temp = last_node;
	prev_node->next = NULL;
	temp->next = *head;
	*head = temp;
}

void	rra(t_stack **astack)
{
	reverse_rotate(astack);
	store_op(7);
}

void	rrb(t_stack **bstack)
{
	reverse_rotate(bstack);
	store_op(8);
}

void	rrr(t_stack **astack, t_stack **bstack)
{
	reverse_rotate(astack);
	reverse_rotate(bstack);
	store_op(9);
}

void	do_rrr(t_stack **astack, t_stack **bstack)
{
	reverse_rotate(astack);
	reverse_rotate(bstack);
}
