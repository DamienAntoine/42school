#include "../includes/push_swap.h"

t_stack	*find_bf(t_stack **a_stack_head, t_stack **b_stack_head)
{
    long int	best_buddy;
    long int	counter;
    long int	tmp;
    t_stack		*temp;
    t_stack		*best_buddy_node = NULL;

    counter = __LONG_LONG_MAX__;
    best_buddy = __LONG_LONG_MAX__;
    temp = *a_stack_head;
    while (*a_stack_head)
    {
        tmp = (*a_stack_head)->value - (*b_stack_head)->value;
        if ((tmp < counter) && ((*a_stack_head)->value > (*b_stack_head)->value))
        {
            counter = tmp;
            best_buddy = (*a_stack_head)->value;
            best_buddy_node = *a_stack_head;
        }
        (*a_stack_head) = (*a_stack_head)->next;
    }
    *a_stack_head = temp;
    if (best_buddy == __LONG_LONG_MAX__)
        return (NULL);
    return (best_buddy_node);
}
