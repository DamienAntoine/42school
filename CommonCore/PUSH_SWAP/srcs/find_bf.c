#include "../includes/push_swap.h"

t_stack		*find_bf(t_stack **a_stack_node, t_stack **b_stack_head)
{
	int		bf;
	int		tempcost;
	t_stack	*bstack;
	t_stack *bfnode;

	bf = 2147483647;
	tempcost = 2147483647;
	bstack = *b_stack_head;
	bfnode = NULL;
	while (bstack)
	{
		if (bstack->value < (*a_stack_node)->value && bstack->value < bf)
		{
			bf = bstack->value;
			bfnode = bstack;
			if (cost_to_top(*b_stack_head, bfnode->value) < tempcost)
				tempcost = cost_to_top(*b_stack_head, bfnode->value);
		}
		bstack = bstack->next;
	}
	return (bfnode);
}