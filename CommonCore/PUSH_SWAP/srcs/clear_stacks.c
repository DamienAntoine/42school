/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_stacks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:21:51 by dantoine          #+#    #+#             */
/*   Updated: 2024/06/04 12:22:19 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	free_stack(t_stack *a_stack)
{
	t_stack	*temp;

	while (a_stack)
	{
		temp = a_stack->next;
		free(a_stack);
		a_stack = temp;
	}
}
