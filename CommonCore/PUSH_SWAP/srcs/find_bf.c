#include "../includes/push_swap.h"

t_stack		*find_bf(t_stack **a_stack_node, t_stack **b_stack_head)
{
	int		bf;
	t_stack	*bstack;

	bf = 2147483647;
	bstack = *b_stack_head;
	while (bstack)
	{
		if (bstack->value > (*a_stack_node)->value && bstack->value < bf)
		{
			bf = bstack->value;
			break ;
		}
		bstack = bstack->next;
	}
	return (bstack);
}