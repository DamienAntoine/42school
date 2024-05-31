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
int	cost_to_top_both_helper(t_stack *atemp, t_stack *btemp, int avalue, int bvalue, int cost)
{
	if (is_closer_to_top(atemp, avalue) && is_closer_to_top(btemp, bvalue))
	{
		while (atemp->value != avalue && btemp->value != bvalue)
		{
			atemp = atemp->next;
			btemp = btemp->next;
			cost++;
		}
	}
	else if (!is_closer_to_top(atemp, avalue) && !is_closer_to_top(btemp, bvalue))
	{
		while (atemp->value != avalue && btemp->value != bvalue)
		{
			atemp = atemp->next;
			btemp = btemp->next;
		}
		while (atemp && btemp)
		{
			atemp = atemp->next;
			btemp = btemp->next;
			cost++;
		}
	}
	return (cost);
}

int	cost_to_top_both(t_stack *astack, t_stack *bstack, int avalue, int bvalue)
{
	int	cost;
	t_stack *atemp;
	t_stack *btemp;

	cost = 0;
	atemp = astack;
	btemp = bstack;
	if (atemp->value == avalue && btemp->value != bvalue)
        return (cost_to_top(bstack, bvalue));
	else if (btemp->value == bvalue && atemp->value != avalue)
        return (cost_to_top(astack, avalue));
	if (is_closer_to_top(atemp, avalue) && is_closer_to_top(btemp, bvalue))
		cost += cost_to_top_both_helper(atemp, btemp, avalue, bvalue, cost);
	else if (!is_closer_to_top(atemp, avalue) && !is_closer_to_top(btemp, bvalue))
		cost += cost_to_top_both_helper(atemp, btemp, avalue, bvalue, cost);
	if (btemp->value == bvalue)
		return (cost + cost_to_top(atemp, avalue));
	else if (atemp->value == avalue)
		return (cost + cost_to_top(btemp, bvalue));
	else if (is_closer_to_top(atemp, avalue) && !is_closer_to_top(btemp, bvalue))
	{
		cost += cost_to_top(astack, avalue);
		cost += cost_to_top(bstack, bvalue);
	}
	else if (!is_closer_to_top(atemp, avalue) && is_closer_to_top(btemp, bvalue))
	{
		cost += cost_to_top(astack, avalue);
		cost += cost_to_top(bstack, bvalue);
	}
	return (cost);	
}

int cost_to_top(t_stack *stack_head, int value)
{
    int cost = 0;
	int reverse_cost;
	int size;
    t_stack *node;

	node = stack_head;
	//printf("\nvalue %d  nodevalue %d", value, node->value);
    while (node != NULL && node->value != value)
	{
        cost++;
        node = node->next;
    }
    size = 0;
    node = stack_head;
    while (node != NULL)
	{
        size++;
        node = node->next;
    }
	reverse_cost = size - cost;
	//printf("\ncost %d", cost);
	//printf("\nrevcost %d", reverse_cost);
	//printf("\nsize %d", size);
	if (cost < reverse_cost)
	{
		//printf("cost\n");
		return (cost);
	}
	else
	{
		//printf("reverse cost\n");
    	return (reverse_cost);
	}
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
	if (index_temp <= (i / 2))
		return (1);
	else
		return (0);
}
