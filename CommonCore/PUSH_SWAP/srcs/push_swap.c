#include "../includes/push_swap.h"

void		until_five(t_stack **astack_head, t_stack **bstack_head)
{
	int	counter;
	t_stack *astack;
	int	mean;
	int	target;

	counter = 0;
	astack = *astack_head;
	while (astack)
	{
		counter++;
		astack = astack->next;
	}
	while (counter > 5)
	{
		mean = find_mean_value(astack_head);
		if (mean == -1)
        {
            ft_printf("Error: Unable to calculate mean value\n");
            return;
        }
		if ((*astack_head)->value > mean)
		{
			target = (*astack_head)->value;
			if (is_closer_to_top(*astack_head, target))
				ra(astack_head);
			else
				rra(astack_head);
		}
		else if ((*astack_head)->value <= mean)
			untilfive_helper(astack_head, bstack_head, &counter);
	}
}

void	untilfive_helper(t_stack **astack_head, t_stack **bstack_head, int *counter)
{
	pb(astack_head, bstack_head);
	(*counter)--;
}