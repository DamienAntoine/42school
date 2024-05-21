#include "../includes/push_swap.h"

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
	if (!is_closer_to_top(bstack_head, value))
		to_last_node(bstack_head);
	while (node != NULL && node->value != value)
	{
		cost++;
		node = node->next;
	}
	return (cost);
}

int		is_closer_to_top(t_stack *bstack_head, int value)
{
	t_stack *temp;
	int	counter;
	int	i;
	int	index_temp;

	temp = bstack_head;
	counter = 0;
	i = 0;
	while (temp)
	{
		counter++;
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