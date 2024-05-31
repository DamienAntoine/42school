#include "../includes/push_swap.h"

//return the best fit pair
t_bf *find_best_fit(t_stack **astack, t_stack **bstack)
{
    t_bf *pairs;

    pairs = find_pairs(astack, bstack);
    pairs = cheapest_pair(pairs);
    return (pairs);
}

//find target position of each astack nodes in bstack
t_bf *find_pairs(t_stack **astack, t_stack **bstack)
{
    
}

//calculate the cost for each pairs
t_bf *cheapest_pair(t_bf *pairs)
{

}
