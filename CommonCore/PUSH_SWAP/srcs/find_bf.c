#include "../includes/push_swap.h"

t_bf *find_optimal_nodes(t_stack **astack_head, t_stack **bstack_head)
{
    t_stack *a_temp, *b_temp;
    t_bf *optimal_pair = malloc(sizeof(t_bf));
    int a_cost;
    int b_cost;
    int total_cost;
    int min_difference = __INT_MAX__;

    optimal_pair->cost = __INT_MAX__;
    a_temp = *astack_head;
    while (a_temp)
    {
        b_temp = *bstack_head;
        while (b_temp)
        {
            if (a_temp->value > b_temp->value)
            {
                int difference = a_temp->value - b_temp->value;
                if (difference < min_difference)
                {
                    min_difference = difference;
                    a_cost = cost_to_top(*astack_head, a_temp->value);
                    b_cost = cost_to_top(*bstack_head, b_temp->value);
                    total_cost = a_cost + b_cost;
                    if (total_cost < optimal_pair->cost)
                    {
                        optimal_pair->a_node = a_temp;
                        optimal_pair->b_node = b_temp;
                        optimal_pair->cost = total_cost;
                    }
                }
            }
            b_temp = b_temp->next;
        }
        a_temp = a_temp->next;
    }
    if (optimal_pair->cost == __INT_MAX__)
    {
        free(optimal_pair);
        return NULL;
    }
    return optimal_pair;
}

//trouver pairs
//trouver la pair avec le plus petit cout

