#include "../includes/push_swap.h"

int		cost_to_top(t_stack *bstack_head, int value)
{
	int		cost;
	t_stack	*node;

	node = bstack_head;
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
		{
			index_temp = i;
		}
		temp = temp->next;
	}
	if (index_temp < (i / 2))
		return (1);
	else
		return (0);
}