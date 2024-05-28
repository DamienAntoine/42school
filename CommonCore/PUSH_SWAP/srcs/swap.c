#include "../includes/push_swap.h"

void	swap(t_stack **head)
{
	t_stack	*temp;

	if (*head == NULL || (*head)->next == NULL)
		return;
	temp = (*head)->next;
	(*head)->next = temp->next;
	temp->next = *head;
	*head = temp;
}

//sa (swap a): Swap the first 2 elements at the top of stack a. Do nothing if there is only one or no elements.
void	sa(t_stack **astack)
{
	swap(astack);
	store_op(4);
}

//sb (swap b): Swap the first 2 elements at the top of stack b. Do nothing if there is only one or no elements.
void	sb(t_stack **bstack)
{
	swap(bstack);
	store_op(5);
}

//ss : sa and sb at the same time.
void	ss(t_stack **astack, t_stack **bstack)
{
	swap(astack);
	swap(bstack);
	store_op(6);
}