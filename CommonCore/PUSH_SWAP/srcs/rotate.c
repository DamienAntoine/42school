/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: dantoine <marvin@42.fr>                    +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/06/04 12:30:53 by dantoine          #+#    #+#             */
/*   Updated: 2024/06/04 12:31:51 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"


void	rotate(t_stack **head)
{
	t_stack *temp;
	t_stack *last_node;

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

// ra (rotate a): Shift up all elements of stack a by 1. The first element becomes the last one.
void	ra(t_stack **astack)
{
	rotate(astack);
	store_op(1);
}

// rb (rotate b): Shift up all elements of stack b by 1. The first element becomes the last one.
void	rb(t_stack **bstack)
{
	rotate(bstack);
	store_op(2);
}

// rr : ra and rb at the same time.
void	rr(t_stack **astack, t_stack **bstack)
{
	rotate(astack);
	rotate(bstack);
	store_op(3);
}
