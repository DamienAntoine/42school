#include "../includes/push_swap.h"

/*t_stack	*find_bf_node(t_stack **a_stack_head, t_stack **b_stack_head)
{
    long int	bf_value;
    long int	counter;
    long int	tmp;
    t_stack		*temp;
    t_stack		*bf_node;

    counter = __LONG_LONG_MAX__;
    bf_value = __LONG_LONG_MAX__;
    temp = *a_stack_head;
	bf_node = NULL;
    while (*a_stack_head)
    {
        tmp = (*a_stack_head)->value - (*b_stack_head)->value;
        if ((tmp < counter) && ((*a_stack_head)->value > (*b_stack_head)->value))
        {
            counter = tmp;
            bf_value = (*a_stack_head)->value;
            bf_node = *a_stack_head;
        }
        (*a_stack_head) = (*a_stack_head)->next;
    }
    *a_stack_head = temp;
    if (bf_value == __LONG_LONG_MAX__)
        return (NULL);
    return (bf_node);
}*/

/*t_bf *find_optimal_nodes(t_stack **astack_head, t_stack **bstack_head)
{
    t_stack *a_temp, *b_temp;
    t_bf *optimal_pair = malloc(sizeof(t_bf));
    int a_cost;
	int b_cost;
	int total_cost;

    optimal_pair->cost = __INT_MAX__;
    a_temp = *astack_head;
    while (a_temp)
    {
        b_temp = *bstack_head;
        while (b_temp)
        {
            if (a_temp->value > b_temp->value)
            {
                a_cost = cost_to_top(*astack_head, a_temp->value);
                b_cost = cost_to_top(*bstack_head, b_temp->value);
                total_cost = a_cost + b_cost;
                if (total_cost < optimal_pair->cost)
                {
                    optimal_pair->a_node = a_temp;
                    optimal_pair->b_node = b_temp;
                    optimal_pair->cost = total_cost;
					ft_printf("anode: %d\n", optimal_pair->a_node->value);
					ft_printf("bnode: %d\n", optimal_pair->b_node->value);
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

