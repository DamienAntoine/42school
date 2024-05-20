#include "../includes/push_swap.h"

void	populate_struct(int value, t_stack **head)
{
	t_stack *new_node;

	if (head == NULL)
        return;
	new_node = malloc(sizeof(t_stack));
    if (new_node == NULL)
		return;
    new_node->value = value;
    new_node->next = *head;
    *head = new_node;
}

void    process_args(char **args, t_stack **head)
{
    int i;
	int	j;
    int num;
	char	**splitarg;

    i = 0;
	if (args[i] == NULL)
		return;
    while (args[i])
    {
		splitarg = ft_split(args[i], ' ');
		if (splitarg == NULL)
			perror("Memory Allocation Failed\n");
		j = 0;
		while (splitarg[j])
		{
			num = ft_atoi(splitarg[j]);
			populate_struct(num, head);
			j++;
		}
		free(splitarg);
		i++;
    }
}

int		is_sorted(t_stack *a_stack)
{
	/*if (!a_stack)
		return (1);*/
	while (a_stack->next != NULL)
	{
		if ((a_stack->next->value) < (a_stack->value))
			return (0);
		a_stack = a_stack->next;
	}
	return (1);
}

void	algo(t_stack **astack_head, t_stack **bstack_head)
{
	while (!is_sorted(*astack_head))
	{
		until_five(astack_head, bstack_head);
		sort_five(astack_head, bstack_head);
		bf_on_top(astack_head, bstack_head);
	}
}

int main(int argc, char **argv)
{
	t_stack		*a_stack;
	t_stack		*b_stack;

	b_stack = NULL;
    if (argc < 2)
	{
		write(2, "Error\n", 6);
	    return (0);
	}
	//error handling
    if (!check_inputs(argc, argv))
	{
		ft_printf("Input Error\n");
		return (1);
	}
	process_args(argv, &a_stack);
	algo(&a_stack, &b_stack);
	free_stack(a_stack);
	free_stack(b_stack);
	return (0);
}
