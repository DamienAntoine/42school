#include "../includes/push_swap.h"

/*
t_stack		*find_bf(t_stack **a_stack_node, t_stack **b_stack_head)
{
    int		bf;
    int		tempcost;
    int     newcost;
    t_stack	*bstack;
    t_stack *bfnode;

    bf = 2147483647;
    tempcost = 2147483647;
    bstack = *b_stack_head;
    bfnode = NULL;
    while (bstack)
    {
        if (bstack->value < (*a_stack_node)->value && bstack->value < bf)
        {
            bf = bstack->value;
            bfnode = bstack;
            newcost = cost_to_top(*b_stack_head, bfnode->value);
            if (newcost < tempcost)
                tempcost = newcost;
        }
        bstack = bstack->next;
    }
    return (bfnode);
}
*/

t_stack		*find_bf(t_stack **a_stack_head, t_stack **b_stack_head)
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
}
