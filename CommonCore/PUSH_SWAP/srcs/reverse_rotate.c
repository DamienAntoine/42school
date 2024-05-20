#include "../includes/push_swap.h"

void	reverse_rotate(t_stack **head)
{
	t_stack *temp;
	t_stack	*last_node;
	t_stack	*prev_node;

	prev_node = NULL;
	if (*head == NULL || (*head)->next == NULL)
                return ;
	last_node = *head;
    while (last_node->next)
	{
		prev_node = last_node;
        last_node = last_node->next;
	}
    temp = last_node;
    prev_node->next = NULL;
    temp->next = *head;
    *head = temp;
}

//rra (reverse rotate a): Shift down all elements of stack a by 1. The last element becomes the first one.
void	rra(t_stack **astack)
{
	reverse_rotate(astack);
	ft_printf("ra\n");
}

//rrb (reverse rotate b): Shift down all elements of stack b by 1. The last element becomes the first one.
void	rrb(t_stack **bstack)
{
	reverse_rotate(bstack);
	ft_printf("rb\n");
}

//rrr : rra and rrb at the same time.
void	rrr(t_stack **astack, t_stack **bstack)
{
	reverse_rotate(astack);
	reverse_rotate(bstack);
	ft_printf("rr\n");
}