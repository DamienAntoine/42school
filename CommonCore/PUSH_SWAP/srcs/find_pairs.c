#include "../includes/push_swap.h"

t_stack *find_min_a_node(t_stack *astack, int b_value)
{
    t_stack *min_astack;

    min_astack = NULL;
    while (astack)
    {
        if (astack->value > b_value && (!min_astack || astack->value < min_astack->value))
            min_astack = astack;
        astack = astack->next;
    }
    return (min_astack);
}

void append_pair(t_bf **head, t_bf **tail, t_stack *astack, t_stack *bstack)
{
    t_bf *new_pair;

    new_pair = (t_bf *)malloc(sizeof(t_bf));
    new_pair->a_node = astack;
    new_pair->b_node = bstack;
    new_pair->next = NULL;
    if (!*head)
    {
        *head = new_pair;
        *tail = new_pair;
    }
    else
    {
        (*tail)->next = new_pair;
        *tail = new_pair;
    }
}

t_bf *find_pairs(t_stack *astack_head, t_stack *bstack_head)
{
    t_bf *head;
    t_bf *tail;
    t_stack *min_a_node;

    head = NULL;
    tail = NULL;
    while (bstack_head)
    {
        min_a_node = find_min_a_node(astack_head, bstack_head->value);
        if (min_a_node)
            append_pair(&head, &tail, min_a_node, bstack_head);
        bstack_head = bstack_head->next;
    }
    return (head);
}