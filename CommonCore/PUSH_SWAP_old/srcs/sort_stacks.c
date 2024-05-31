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

void insert_sorted(t_stack **astack, t_stack **bstack)
{
	t_bf *bfnode;

    if (astack == NULL || bstack == NULL || *bstack == NULL)
        return;
    bfnode = find_optimal_nodes(astack, bstack);
	if (bfnode == NULL)
		return;
	//printf("\nastack val: %d, bfnode a val: %d\n", (*astack)->value, bfnode->a_node->value);
	put_on_top_both(astack, bstack, bfnode->a_node->value, bfnode->b_node->value);
    pa(astack, bstack);
}

void	back_to_astack(t_stack **astack, t_stack **bstack)
{
    while (*bstack)
    {
        //printf("\n");
        //print_stacks(astack, bstack);
        //printf("\n");
        insert_sorted(astack, bstack);
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

void put_on_top(t_stack **astack_head, int value)
{
    if (is_closer_to_top(*astack_head, value))
    {
        while ((*astack_head)->value != value)
            ra(astack_head);
    }
    else
    {
        while ((*astack_head)->value != value)
            rra(astack_head);
    }
}

void put_on_top_bstack(t_stack **bstack_head, int value)
{
    if (is_closer_to_top(*bstack_head, value))
    {
        while ((*bstack_head)->value != value)
            rb(bstack_head);
    }
    else
    {
        while ((*bstack_head)->value != value)
            rrb(bstack_head);
    }
}

void put_on_top_both(t_stack **astack_head, t_stack **bstack_head, int avalue, int bvalue)
{
    int astack_value = (*astack_head)->value;
    int bstack_value = (*bstack_head)->value;
    
    while (astack_value != avalue && bstack_value != bvalue)
    {
        if (is_closer_to_top(*astack_head, astack_value) && is_closer_to_top(*bstack_head, bstack_value))
            rr(astack_head, bstack_head);
        else if (!is_closer_to_top(*astack_head, astack_value) && !is_closer_to_top(*bstack_head, bstack_value))
            rrr(astack_head, bstack_head);
        else if (is_closer_to_top(*astack_head, astack_value))
            ra(astack_head);
        else if (is_closer_to_top(*bstack_head, bstack_value))
            rb(bstack_head);
		else if (!is_closer_to_top(*astack_head, astack_value))
            rra(astack_head);
        else if (!is_closer_to_top(*bstack_head, bstack_value))
            rrb(bstack_head);
        
        astack_value = (*astack_head)->value;
        bstack_value = (*bstack_head)->value;
    }
    if (astack_value != avalue)
        put_on_top(astack_head, avalue);
    else if (bstack_value != bvalue)
        put_on_top_bstack(bstack_head, bvalue);
}

void		until_three(t_stack **astack_head, t_stack **bstack_head)
{
    int		biggest;
    int     i;

    i = 0;
    while (i < 2)
    {
        biggest = find_biggest(astack_head);
        put_on_top(astack_head, biggest);
        pb(astack_head, bstack_head);
        i++;
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
    until_three(&astack, &bstack);
    smallest = find_smallest(&astack);
    biggest = find_biggest(&astack);
    sort_three(&astack, smallest, biggest);
    sb(&bstack);
    pa(&astack, &bstack);
    pa(&astack, &bstack);
    ra(&astack);
    ra(&astack);
    back_to_astack(&astack, &bstack);
    *astack_head = astack;
    *bstack_head = bstack;
}
