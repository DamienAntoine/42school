#include "../includes/push_swap.h"

void populate_struct(int value, t_stack **astack_head)
{
    t_stack *new_node;
    t_stack *last_node;

    new_node = malloc(sizeof(t_stack));
    if (new_node == NULL)
        return;
    new_node->value = value;
    new_node->next = NULL;
    if (*astack_head == NULL)
    {
        *astack_head = new_node;
        return;
    }
    last_node = *astack_head;
    while (last_node->next != NULL)
        last_node = last_node->next;

    last_node->next = new_node;
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

void process_args(char **args, t_stack **astack_head)
{
    int i;
    int j;
    int num;
    char **splitarg;

    i = 1;
    while (args[i])
    {
        splitarg = ft_split(args[i], ' ');
        if (splitarg == NULL)
            return;
        j = 0;
        while (splitarg[j])
        {
            num = ft_atoi(splitarg[j]);
            populate_struct(num, astack_head);
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