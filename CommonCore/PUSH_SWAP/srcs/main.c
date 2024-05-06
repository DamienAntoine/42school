#include "../includes/push_swap.h"

t_stack		*head;

void	populate_struct(int value)
{
	t_stack *new_node;
	
	new_node = malloc(sizeof(t_stack));
    if (new_node == NULL) {
        ft_printf("Memory Allocation Failed\n");
        return;
    }
    new_node->value = value;
    new_node->next = head;
    head = new_node;
}

void    process_args(char **args)
{
    int i;
	int	j;
    int num;
	int flag;
    char    *arg_cpy;
	char	**splitarg;

    i = 0;
    while (args[i])
    {
		j = 0;
		flag = 0;
		while (args[i][j])
		{
			if (args[i][j] == ' ')
			{
				splitarg = ft_split(args, ' ');
				flag = 1;
			}
			j++;
		}
        arg_cpy = ft_strdup(args[i]);
        num = ft_atoi(arg_cpy);
        free(arg_cpy);
		populate_struct(num);
		i++;
    }
}
//todo: count how many numbers, allocate memory and create nodes for all these numbers, populate these nodes with the numbers
int main(int argc, char **argv)
{
	int		i;
	int		j;
	int		spaceflag;

    if (argc < 2)
	    return (0);
		process_args(argv);
    if (!check_input(argv))
	{
	    ft_printf("Invalid Arguments\n");
		return (1);
	}
    i = 0;
    while (argv[i])
    {
		j = 0;
		spaceflag = 0;
        while (argv[i][j])
        {
            if (argv[i][j] == ' ')
				spaceflag = 1;
            j++;
        }
		if (spaceflag == 0)
        	populate_struct(ft_atoi(argv[i]));
		else if (spaceflag == 1)
			handle_arrays(ft_split(argv[i], ' '));
        i++;
    }
	return (0);
}
