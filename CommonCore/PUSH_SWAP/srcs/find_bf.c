#include "../includes/push_swap.h"

t_bf *find_optimal_nodes(t_stack *astack_head, t_stack *bstack_head)
{
    t_bf *pairs;
    t_bf *optimal;
    t_bf *result;

    pairs = find_pairs(astack_head, bstack_head);
    optimal = find_smaller_cost(pairs, astack_head, bstack_head);
    result = NULL;
    if (optimal)
    {
        result = (t_bf *)malloc(sizeof(t_bf));
        if (!result)
            return NULL;
        *result = *optimal;
        result->next = NULL;
    }
    free_pairs(pairs);
    return result;
}

void free_pairs(t_bf *pairs)
{
    t_bf *tmp;

    while (pairs)
    {
        tmp = pairs;
        pairs = pairs->next;
        free(tmp);
    }
}

t_bf *find_smaller_cost(t_bf *optimal_pairs, t_stack *astack_head, t_stack *bstack_head)
{
    t_bf *best_cost;
    t_bf *current;

    best_cost = optimal_pairs;
    current = optimal_pairs;
    if (optimal_pairs == NULL)
        return (NULL);
    best_cost->cost = cost_to_top(astack_head, current->a_node->value) +
                      cost_to_top(bstack_head, current->b_node->value);
    current = current->next;
    while (current)
    {
        current->cost = cost_to_top(astack_head, current->a_node->value) +
                        cost_to_top(bstack_head, current->b_node->value);
        if (current->cost < best_cost->cost)
            best_cost = current;
        current = current->next;
    }
    return (best_cost);
}
