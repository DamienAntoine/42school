/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:58:59 by dantoine          #+#    #+#             */
/*   Updated: 2024/06/04 12:59:26 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	swap(t_stack **head)
{
	t_stack	*temp;

	if (*head == NULL || (*head)->next == NULL)
		return ;
	temp = (*head)->next;
	(*head)->next = temp->next;
	temp->next = *head;
	*head = temp;
}

void	sa(t_stack **astack)
{
	swap(astack);
	store_op(4);
}

void	sb(t_stack **bstack)
{
	swap(bstack);
	store_op(5);
}

void	ss(t_stack **astack, t_stack **bstack)
{
	swap(astack);
	swap(bstack);
	store_op(6);
}
