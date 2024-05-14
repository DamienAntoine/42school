#include "../includes/push_swap.h"

void		until_five(t_stack **astack_head, t_stack **bstack_head)
{
	int	counter;
	t_stack *temp;
	int	mean;

	mean = 0;
	counter = 0;
	temp = *astack_head;
	while (temp)
	{
		counter++;
		temp = temp->next;
	}
	while (counter > 5)
	{
		mean = find_mean_value(*astack_head);
		if ((*astack_head)->value > mean)
			ra(*astack_head);
		else if ((*astack_head)->value < mean)
		{
			pb(*astack_head, *bstack_head);
			*astack_head = (*astack_head)->next;
		}
		counter--;
	}
}