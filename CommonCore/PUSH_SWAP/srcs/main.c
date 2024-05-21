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

void	free_args(char **args)
{
	int	k;

	k = 0;
	while (args[k])
	{
		free(args[k]);
		k++;
	}
	free(args);
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
			return;
		j = 0;
		while (splitarg[j])
		{
			num = ft_atoi(splitarg[j]);
			populate_struct(num, head);
			j++;
		}
		free_args(splitarg);
		i++;
    }
}

int		is_sorted(t_stack *a_stack)
{
	if (a_stack == NULL)
		return (1);
	while (a_stack->next != NULL)
	{
		if ((a_stack->next->value) < (a_stack->value))
			return (0);
		a_stack = a_stack->next;
	}
	return (1);
}
int		argcounter(t_stack *astack_head)
{
	t_stack *temp;
	int argcount;

	temp = astack_head;
	argcount = 0;
	while (temp)
	{
		argcount++;
		temp = temp->next;
	}
	return (argcount);
}

void	algo(t_stack **astack_head, t_stack **bstack_head)
{
	int argcount;

	argcount = argcounter(*astack_head);
	if (argcount == 1)
		return;
	while (!is_sorted(*astack_head))
	{
		if (argcount > 5)
			until_five(astack_head, bstack_head);
		else if (argcount <= 5)
			sort_five(astack_head, bstack_head);
		bf_on_top(astack_head, bstack_head);
	}
}

int main(int argc, char **argv)
{
	t_stack		*a_stack;
	t_stack		*b_stack;

	a_stack = NULL;
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
	if (is_sorted(a_stack) == 1)
		return (1);
	algo(&a_stack, &b_stack);
	free_stack(a_stack);
	//free_stack(b_stack);
	return (0);
}
