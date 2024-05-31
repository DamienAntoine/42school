#include "../includes/push_swap.h"

void	sort_three(t_stack **astack_head, int smallest, int biggest)
{
    if ((*astack_head)->value == smallest && (*astack_head)->next->value != biggest)
        return ;
    else if ((*astack_head)->value == smallest && (*astack_head)->next->value == biggest)
    {
        sa(astack_head);
        ra(astack_head);
    }
    else if ((*astack_head)->value != biggest && (*astack_head)->next->value == smallest)
        sa(astack_head);
    else if ((*astack_head)->value != biggest && (*astack_head)->value != smallest && (*astack_head)->next->value == biggest)
        rra(astack_head);
    else if ((*astack_head)->value == biggest && (*astack_head)->next->value == smallest)
        ra(astack_head);
    else if ((*astack_head)->value == biggest && (*astack_head)->next->value != smallest)
    {
        ra(astack_head);
        sa(astack_head);
    }
}

void sort_four(t_stack **astack_head, t_stack **bstack_head)
{
    int smallest = find_smallest(astack_head);
    put_on_top(astack_head, smallest);
    pb(astack_head, bstack_head);
    sort_three(astack_head, find_smallest(astack_head), find_biggest(astack_head));
    pa(astack_head, bstack_head);
}

int			find_smallest(t_stack **stack_head)
{
	t_stack		*stack;
	int			smallest;

	smallest = 2147483647;
	stack = *stack_head;
	while (stack)
	{
		if (stack->value < smallest)
			smallest = stack->value;
		stack = stack->next;
	}
	return (smallest);
}

void		until_three(t_stack **astack_head, t_stack **bstack_head)
{
    t_bf *best_fit;

    pb(astack_head, bstack_head);
    pb(astack_head, bstack_head);
    while (stack_length(astack_head) > 3)
    {
        best_fit = find_best_fit(astack_head, bstack_head);
        put_on_top_both(astack_head, bstack_head, best_fit->a_node->value, best_fit->b_node->value);
        pb(astack_head, bstack_head);
    }
}

void	sort_stacks(t_stack **astack_head, t_stack **bstack_head)
{
    t_stack	*astack;
    t_stack	*bstack;
    int		smallest;
    int		biggest;

    astack = *astack_head;
    bstack = *bstack_head;
    if (stack_length(astack_head) >= 5)
        until_three(&astack, &bstack);
    sort_three(&astack, smallest, biggest);
    //back_to_astack
    *astack_head = astack;
    *bstack_head = bstack;
}
