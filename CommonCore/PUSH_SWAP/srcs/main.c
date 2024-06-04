/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:42:06 by dantoine          #+#    #+#             */
/*   Updated: 2024/06/04 12:43:29 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	algo(t_stack **astack_head, t_stack **bstack_head)
{
	int	smallest;
	int	biggest;

	smallest = find_smallest(astack_head);
	biggest = find_biggest(astack_head);
	if ((!is_sorted(*astack_head)) || (*bstack_head) != NULL)
	{
		if (argcounter(*astack_head) > 5)
			until_five(astack_head, bstack_head);
		if (argcounter(*astack_head) == 3)
			sort_three(astack_head, smallest, biggest);
		if (argcounter(*astack_head) == 4)
			sort_four(astack_head, bstack_head);
		if (argcounter(*astack_head) == 5)
			sort_stacks(astack_head, bstack_head);
		if (!is_sorted(*astack_head))
			put_on_top(astack_head, find_smallest(astack_head));
		if (is_sorted(*astack_head))
			store_op(0);
	}
}

int	main(int argc, char **argv)
{
	t_stack	*a_stack;
	t_stack	*b_stack;

	a_stack = NULL;
	b_stack = NULL;
	if (argc < 2)
	{
		write(2, "Error\n", 6);
		return (0);
	}
	if (!check_inputs(argc, argv))
	{
		ft_printf("Input Error\n");
		return (1);
	}
	process_args(argv, &a_stack);
	if (is_sorted(a_stack) == 1)
		return (1);
	algo(&a_stack, &b_stack);
	free_stack(a_stack);
	return (0);
}
