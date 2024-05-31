#include "../includes/push_swap.h"

void    free_stack(t_stack *a_stack)
{
    t_stack	*temp;

	while (a_stack)
	{
		temp = a_stack->next;
		free(a_stack);
		a_stack = temp;
	}
}