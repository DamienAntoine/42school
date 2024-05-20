#include "../includes/push_swap.h"

void		until_five(t_stack **astack_head, t_stack **bstack_head)
{
	int	counter;
	t_stack *astack;
	int	mean;

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
		if ((*astack_head)->value > mean)
			ra(astack_head);
		else if ((*astack_head)->value < mean)
		{
			pb(astack_head, bstack_head);
			counter--;
		}
	}
}

void bf_on_top(t_stack **astack_head, t_stack **bstack_head)
{
    t_stack *temp;
    int cost;

    temp = find_bf(astack_head, bstack_head);
    if (temp == NULL)
        return;

    cost = cost_to_top(*bstack_head, temp->value);
    while (cost--)
    {
        if (is_closer_to_top(*bstack_head, temp->value))
            rb(bstack_head);
        else
            rrb(bstack_head);
    }
}