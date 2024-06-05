/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:56:53 by dantoine          #+#    #+#             */
/*   Updated: 2024/06/04 12:57:31 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	rotate(t_stack **head)
{
	t_stack	*temp;
	t_stack	*last_node;

	if (*head == NULL || (*head)->next == NULL)
		return ;
	last_node = *head;
	while (last_node->next)
		last_node = last_node->next;
	temp = (*head)->next;
	(*head)->next = NULL;
	last_node->next = *head;
	*head = temp;
}

void	ra(t_stack **astack)
{
	rotate(astack);
	store_op(1);
}

void	rb(t_stack **bstack)
{
	rotate(bstack);
	store_op(2);
}

void	rr(t_stack **astack, t_stack **bstack)
{
	rotate(astack);
	rotate(bstack);
	store_op(3);
}

void	do_rr(t_stack **astack, t_stack **bstack)
{
	rotate(astack);
	rotate(bstack);
}
