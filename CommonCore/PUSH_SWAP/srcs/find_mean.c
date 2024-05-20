#include "../includes/push_swap.h"

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
	mean /= counter;
	return (mean);
}