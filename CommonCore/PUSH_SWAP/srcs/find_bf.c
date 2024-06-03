#include "../includes/push_swap.h"

/*t_bf *find_optimal_nodes(t_stack **astack_head, t_stack **bstack_head)
{
    t_stack *a_temp;
    t_stack *b_temp;
    t_bf *optimal_pair;
    int a_cost;
    int b_cost;
    int total_cost;
    int min_difference = __INT_MAX__;
    int difference;

    optimal_pair = malloc(sizeof(t_bf));
    optimal_pair->cost = __INT_MAX__;
    a_temp = *astack_head;
    while (a_temp)
    {
        b_temp = *bstack_head;
        while (b_temp)
        {
            if (a_temp->value > b_temp->value)
            {
                difference = a_temp->value - b_temp->value;
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
}*/

t_bf *find_optimal_nodes(t_stack *astack_head, t_stack *bstack_head)
{
    t_bf *optimal_pairs;
    t_bf *optimal_node;
    t_bf *tmp;
    t_bf *result;

    optimal_pairs = find_pairs(astack_head, bstack_head);
    optimal_node = find_smaller_cost(optimal_pairs, astack_head, bstack_head);
    if (optimal_node != NULL)
    {
        result = (t_bf *)malloc(sizeof(t_bf));
        if (result == NULL)
            return (NULL);
        result->a_node = optimal_node->a_node;
        result->b_node = optimal_node->b_node;
        result->cost = optimal_node->cost;
        result->next = NULL;
        while (optimal_pairs != NULL)
        {
            tmp = optimal_pairs;
            optimal_pairs = optimal_pairs->next;
            free(tmp);
        }
        return result;
    }
    while (optimal_pairs != NULL)
    {
        tmp = optimal_pairs;
        optimal_pairs = optimal_pairs->next;
        free(tmp);
    }
    return (NULL);
}

t_bf *find_pairs(t_stack *astack_head, t_stack *bstack_head)
{
    t_bf *head = NULL;
    t_bf *tail = NULL;
    t_bf *new_pair;
    t_stack *a_node;
    t_stack *b_node;
    t_stack *min_a_node;

    b_node = bstack_head;
    while (b_node)
    {
        a_node = astack_head;
        min_a_node = NULL;
        while (a_node)
        {
            if (a_node->value > b_node->value && (min_a_node == NULL || a_node->value < min_a_node->value))
            {
                min_a_node = a_node;
            }
            a_node = a_node->next;
        }

        if (min_a_node != NULL)
        {
            new_pair = (t_bf *)malloc(sizeof(t_bf));
            new_pair->a_node = min_a_node;
            new_pair->b_node = b_node;
            new_pair->next = NULL;

            if (head == NULL)
            {
                head = new_pair;
                tail = new_pair;
            }
            else
            {
                tail->next = new_pair;
                tail = new_pair;
            }
        }

        b_node = b_node->next;
    }
    return (head);
}

t_bf *find_smaller_cost(t_bf *optimal_pairs, t_stack *astack_head, t_stack *bstack_head)
{
    t_bf *best_cost;
    t_bf *current;

    best_cost = optimal_pairs;
    current = optimal_pairs;
    if (optimal_pairs == NULL)
        return NULL;
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
//trouver pairs
//trouver la pair avec le plus petit cout

