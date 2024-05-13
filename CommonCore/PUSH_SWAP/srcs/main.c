#include "../includes/push_swap.h"

void	populate_struct(int value, t_stack **head)
{
	t_stack *new_node;
	
	new_node = malloc(sizeof(t_stack));
    if (new_node == NULL)
		perror("Memory Allocation Failed\n");
    new_node->value = value;
    new_node->next = *head;
	new_node->index;
    *head = new_node;
}

void    process_args(char **args, t_stack **head)
{
    int i;
	int	j;
    int num;
    char    *arg_cpy;
	char	**splitarg;

    i = 0;
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

int main(int argc, char **argv)
{
	int		i;
	t_stack		*a_stack;
	t_stack		*b_stack;

	b_stack = NULL;
    if (argc < 2)
	    return (0);
	i = 0;
    if (!check_input(argv))
		perror("Memory Allocation Failed\n");
	process_args(argv, &a_stack);
	//add algorithm things

	return (0);
}
