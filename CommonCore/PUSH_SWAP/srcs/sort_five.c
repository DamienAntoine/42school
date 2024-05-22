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
	counter = stack_length(&astack);
	while (counter > 3)
	{
		pb(astack_head, bstack_head);
		counter--;
	}
}

void back_to_five(t_stack **astack, t_stack **bstack)
{
    t_stack *current;

    if (astack == NULL || bstack == NULL)
        return;

    while (stack_length(astack) < 5 && *bstack != NULL)
    {
        current = *astack;
        if (current == NULL || (*bstack)->value < current->value)
        {
            pa(astack, bstack);
        }
        else
        {
            pa(astack, bstack);
            sa(astack);
        }
    }
}

void back_to_four(t_stack **astack, t_stack **bstack)
{
    t_stack *current;

    if (astack == NULL || bstack == NULL)
        return;

    while (stack_length(astack) < 4 && *bstack != NULL)
    {
        current = *astack;
        if (current == NULL || (*bstack)->value < current->value)
        {
            pa(astack, bstack);
        }
        else
        {
            pa(astack, bstack);
            sa(astack);
        }
    }
}

int	stack_length(t_stack **astack_head)
{
	int	i;
	t_stack *temp;

	i = 0;
	temp = *astack_head;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}
int	last_three_sorted(t_stack **astack_head)
{
    t_stack *temp;

    temp = *astack_head;
    if (!temp || !temp->next || !temp->next->next)
        return 0;
    while (temp->next->next->next)
        temp = temp->next;
    if (temp->value > temp->next->value)
        return(0);
    if (temp->next)
    {
        temp = temp->next;
        if (temp->next && temp->value > temp->next->value)
            return(0);
    }
    return (1);
}

void	sort_five(t_stack **astack_head, t_stack **bstack_head)
{
    t_stack	*astack;
    t_stack	*bstack;
    int		smallest;
    int		biggest;
	int stack_size;

    astack = *astack_head;
    bstack = *bstack_head;
	stack_size = stack_length(astack_head);
	if (stack_size > 3)
    	until_three(&astack, &bstack);
	smallest = find_smallest(&astack);
    biggest = find_biggest(&astack);
	if (stack_length(&astack) <= 3)
    	sort_three(&astack, smallest, biggest);
	if (stack_size == 5)
    	back_to_five(&astack, &bstack);
	else if (stack_size == 4)
		back_to_four(&astack, &bstack);
	*astack_head = astack;
    *bstack_head = bstack;
}
