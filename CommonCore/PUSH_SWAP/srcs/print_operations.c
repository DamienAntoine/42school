/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:35:51 by dantoine          #+#    #+#             */
/*   Updated: 2024/06/04 15:35:52 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	store_op(int move)
{
	static t_moves	*head;
	static t_moves	*current;
	t_moves			*new_node;

	new_node = malloc(sizeof(t_moves));
	new_node->move = move;
	new_node->next = NULL;
	if (move == 0)
	{
		print_op(head);
		free(new_node);
		return ;
	}
	if (head == NULL)
	{
		head = new_node;
		current = head;
	}
	else
	{
		current->next = new_node;
		current = new_node;
	}
}

void	print_op(t_moves *head)
{
	t_moves	*current;
	t_moves	*to_free;

	current = head;
	while (current != NULL)
	{
		if (current->move >= 1 && current->move <= 5)
		{
			if (current->move == 1)
				ft_printf("ra\n");
			else if (current->move == 2)
				ft_printf("rb\n");
			else if (current->move == 3)
				ft_printf("rr\n");
			else if (current->move == 4)
				ft_printf("sa\n");
			else if (current->move == 5)
				ft_printf("sb\n");
		}
		else if (current->move > 5)
			print_other_op(current);
		to_free = current;
		current = current->next;
		free(to_free);
	}
}

void	print_other_op(t_moves *current)
{
	if (current->move == 6)
		ft_printf("ss\n");
	else if (current->move == 7)
		ft_printf("rra\n");
	else if (current->move == 8)
		ft_printf("rrb\n");
	else if (current->move == 9)
		ft_printf("rrr\n");
	else if (current->move == 10)
		ft_printf("pa\n");
	else if (current->move == 11)
		ft_printf("pb\n");
}
