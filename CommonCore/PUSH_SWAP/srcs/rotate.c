#include "../includes/push_swap.h"

void	rotate(t_stack **head)
{
	t_stack *temp;
	t_stack	*last_node;

	if (*head == NULL || (*head)->next == NULL)
                return ;
	last_node = *head;
    while (last_node->next)
        last_node = last_node->next;
    temp = (*head)->next;
    (*head)->next = NULL;
    last_node->next = *head;
    *head = temp;
	printf("\n");
	print_one_stack(head);
	printf("\n");
}

//ra (rotate a): Shift up all elements of stack a by 1. The first element becomes the last one.
void	ra(t_stack **astack)
{
	rotate(astack);
	ft_printf("ra\n");
}

//rb (rotate b): Shift up all elements of stack b by 1. The first element becomes the last one.
void	rb(t_stack **bstack)
{
	rotate(bstack);
	ft_printf("rb\n");
}

//rr : ra and rb at the same time.
void	rr(t_stack **astack, t_stack **bstack)
{
	rotate(astack);
	rotate(bstack);
	ft_printf("rr\n");
}