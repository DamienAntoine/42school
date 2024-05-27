#include "../includes/push_swap.h"

void	push(t_stack **src_head, t_stack **dest_head)
{
        t_stack *temp;
        
        if (*src_head == NULL)
                return ;
        temp = *src_head;
		*src_head = (*src_head)->next;
        temp->next = *dest_head;
        *dest_head = temp;
		printf("\n");
		print_stacks(src_head, dest_head);
		printf("\n");
}

//pa (push a): Take the first element at the top of b and put it at the top of a. Do nothing if b is empty
void	pa(t_stack **astack, t_stack **bstack)
{
    if (!*bstack)
    {
        return;
    }
	push(bstack, astack);
	ft_printf("pa\n");
}
//pb (push b): Take the first element at the top of a and put it at the top of b. Do nothing if a is empty
void    pb(t_stack **astack, t_stack **bstack)
{
    if (!*astack)
    {
        return;
    }
    push(astack, bstack);
    ft_printf("pb\n");
}
