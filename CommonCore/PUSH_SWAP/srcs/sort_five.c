#include "../includes/push_swap.h"

void	sort_three(t_stack **astack_head, int smallest, int biggest)
{
	t_stack		*astack;

	astack = *astack_head;
	if (astack->value == smallest && astack->next->value != biggest)
		return ;
	else if (astack->value == smallest && astack->next->value == biggest)
	{
		sa(&astack);
		ra(&astack);
	}
	else if (astack->value != biggest && astack->next->value == smallest)
		sa(&astack);
	else if (astack->value != biggest && astack->value != smallest && astack->next->value == biggest)
		rra(&astack);
	else if (astack->value == biggest && astack->next->value == smallest)
		ra(&astack);
	else if (astack->value == biggest && astack->next->value != smallest)
	{
		ra(&astack);
		sa(&astack);
	}
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

int			find_biggest(t_stack **stack_head)
{
	t_stack		*stack;
	int			biggest;

	biggest = -2147483647;
	stack = *stack_head;
	while (stack)
	{
		if (stack->value > biggest)
			biggest = stack->value;
		stack = stack->next;
	}
	return (biggest);
}

void		until_three(t_stack **astack_head, t_stack **bstack_head)
{
	int	counter;
	t_stack *astack;

	counter = 0;
	astack = *astack_head;
	while (astack)
	{
		counter++;
		astack = astack->next;
	}
	while (counter > 3)
	{
		pb(astack_head, bstack_head);
		counter--;
	}
}

void	back_to_five(t_stack *astack, t_stack *bstack)
{
	int		i;
	int		bstackcounter;
	t_stack *current;

	if (astack == NULL || bstack == NULL)
        return;
	current = astack;
	i = 1;
	bstackcounter = 2;
	while (bstackcounter && i <= 3 && current != NULL)
	{
		if (i == 1 && bstack->value < current->value)
			pa(&astack, &bstack);
		else if (i == 2 && bstack->value < current->value)
		{
			pa(&current, &bstack);
			sa(&current);
		}
		else if (i == 3 && bstack->value < current->value)
			reduce_backtofive(current, bstack);
		i++;
		current = current->next;
	}
	i = 0;
	bstackcounter--;
}

void	reduce_backtofive(t_stack *astack, t_stack *bstack)
{
	rra(&astack);
	pa(&astack, &bstack);
	ra(&astack);
	ra(&astack);
}

void	sort_five(t_stack **astack_head, t_stack **bstack_head)
{
    t_stack	*astack;
    t_stack	*bstack;
    int		smallest;
    int		biggest;

    astack = *astack_head;
    bstack = *bstack_head;
    until_three(&astack, &bstack);
	smallest = find_smallest(&astack);
    biggest = find_biggest(&astack);
    sort_three(&astack, smallest, biggest);
    back_to_five(astack, bstack);
}