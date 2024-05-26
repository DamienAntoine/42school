#include "../includes/push_swap.h"

/*t_stack		*find_bf(t_stack **a_stack_head, t_stack **b_stack_head)
{
    long int	bf_diff;
    long int	temp_diff;
    int         bf_cost;
    int         temp_cost;
    t_stack	*astack;
    t_stack *bfnode;

    bf_diff = __LONG_LONG_MAX__;
    bf_cost = __INT_MAX__;
    astack = *a_stack_head;
    bfnode = NULL;
    while (astack)
    {
        if (astack->value > (*b_stack_head)->value)
        {
            temp_diff = astack->value - (*b_stack_head)->value;
            if (temp_diff < bf_diff)
            {
                temp_cost = cost_to_top(*a_stack_head, astack->value);
                if (temp_cost < bf_cost)
                {
                    bf_diff = temp_diff;
                    bf_cost = temp_cost;
                    bfnode = astack;
                }
            }
        }
        astack = astack->next;
    }
    return (bfnode);
}*/

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