#include "../includes/push_swap.h"

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

t_stack	*to_last_node(t_stack *stack)
{
	if (stack == NULL)
		return (NULL);
	while (stack->next != NULL)
	{
		stack = stack->next;
	}
	return (stack);
}

int		cost_to_top(t_stack *bstack_head, int value)
{
	int		cost;
	t_stack	*node;

	cost = 0;
	node = bstack_head;
	if (node->next == NULL)
		return (0);
	if (is_closer_to_top(bstack_head, value))
		while (node != NULL && node->value != value)
		{
			cost++;
			node = node->next;
		}
	else
	{
		while (node->value != value)
			node = node->next;
		while (node)
		{
			cost++;
			node = node->next;
		}
	}	
	return (cost);
}

int		is_closer_to_top(t_stack *bstack_head, int value)
{
	t_stack *temp;
	int	i;
	int	index_temp;

	temp = bstack_head;
	i = 0;
	if (temp->value == value)
		return (-1);
	while (temp)
	{
		i++;
		temp->index = i;
		if (temp->value == value)
			index_temp = i;
		temp = temp->next;
	}
	if (index_temp < (i / 2))
		return (1);
	else
		return (0);
}
