#include "../includes/push_swap.h"

void put_on_top(t_stack **astack_head, int value)
{
    if (is_closer_to_top(*astack_head, value))
    {
        while ((*astack_head)->value != value)
            ra(astack_head);
    }
    else
    {
        while ((*astack_head)->value != value)
            rra(astack_head);
    }
}

void put_on_top_bstack(t_stack **bstack_head, int value)
{
    if (is_closer_to_top(*bstack_head, value))
    {
        while ((*bstack_head)->value != value)
            rb(bstack_head);
    }
    else
    {
        while ((*bstack_head)->value != value)
            rrb(bstack_head);
    }
}

void put_on_top_both(t_stack **astack_head, t_stack **bstack_head, int avalue, int bvalue)
{
    int astack_value = (*astack_head)->value;
    int bstack_value = (*bstack_head)->value;
    
    while (astack_value != avalue && bstack_value != bvalue)
    {
        if (is_closer_to_top(*astack_head, astack_value) && is_closer_to_top(*bstack_head, bstack_value))
            rr(astack_head, bstack_head);
        else if (!is_closer_to_top(*astack_head, astack_value) && !is_closer_to_top(*bstack_head, bstack_value))
            rrr(astack_head, bstack_head);
        else if (is_closer_to_top(*astack_head, astack_value))
            ra(astack_head);
        else if (is_closer_to_top(*bstack_head, bstack_value))
            rb(bstack_head);
        
        astack_value = (*astack_head)->value;
        bstack_value = (*bstack_head)->value;
    }
    
    if (astack_value != avalue)
        put_on_top(astack_head, avalue);
    else if (bstack_value != bvalue)
        put_on_top_bstack(bstack_head, bvalue);
}