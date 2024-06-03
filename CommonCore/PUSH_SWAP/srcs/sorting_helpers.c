#include "../includes/push_swap.h"

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

int	find_mean_value(t_stack **head)
{
	int	mean;
	int	counter;
	t_stack *stack;

	mean = 0;
	counter = 0;
	stack = *head;
	while (stack)
	{
		mean += stack->value;
		counter++;
		stack = stack->next;
	}
	if (counter == 0)
        return (-1);
	mean /= counter;
	return (mean);
}