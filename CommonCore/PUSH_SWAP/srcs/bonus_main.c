#include "../includes/push_swap.h"
#include "../includes/get_next_line.h"

void    process_instructions(t_stack **astack, t_stack **bstack)
{
    t_checker  *instructions;
    t_checker  *head;

    instructions = (t_checker *)malloc(sizeof(t_checker));
    instructions->next = NULL;
    head = instructions;
    while (1)
    {
        instructions->line = get_next_line(0);
        if (instructions->line == NULL)
            break;
        if (check_instructions(instructions->line) == 0)
            {
                write(2, "Error\n", 6);
                exit(1);
            }
        instructions->next = (t_checker *)malloc(sizeof(t_checker));
        instructions->next->next = NULL;
        instructions = instructions->next;
    }
    perform_instructions(astack, bstack, head);
    free_moves(head);
}

int     check_instructions(char *line)
{
    if (ft_strncmp(line, "sa", 2) == 0)
        return (1);
    else if (ft_strncmp(line, "sb", 2) == 0)
        return (1);
    else if (ft_strncmp(line, "ss", 2) == 0)
        return (1);
    else if (ft_strncmp(line, "pa", 2) == 0)
        return (1);
    else if (ft_strncmp(line, "pb", 2) == 0)
        return (1);
    else if (ft_strncmp(line, "ra", 2) == 0)
        return (1);
    else if (ft_strncmp(line, "rb", 2) == 0)
        return (1);
    else if (ft_strncmp(line, "rr", 2) == 0)
        return (1);
    else if (ft_strncmp(line, "rra", 3) == 0)
        return (1);
    else if (ft_strncmp(line, "rrb", 3) == 0)
        return (1);
    else if (ft_strncmp(line, "rrr", 3) == 0)
        return (1);
    else
        return (0);
}

void perform_instructions(t_stack **astack, t_stack **bstack, t_checker *instructions)
{
    while (instructions->next)
    {
        run_op(astack, bstack, instructions->line);
        instructions = instructions->next;
    }
}

void run_op(t_stack **astack, t_stack **bstack, char *line)
{
    if (ft_strncmp(line, "sa", 2) == 0)
        swap(astack);
    else if (ft_strncmp(line, "sb", 2) == 0)
        swap(bstack);
    else if (ft_strncmp(line, "ss", 2) == 0)
        do_ss(astack, bstack);
    else if (ft_strncmp(line, "pa", 2) == 0)
        push(bstack, astack);
    else if (ft_strncmp(line, "pb", 2) == 0)
        push(astack, bstack);
    else if (ft_strncmp(line, "ra", 2) == 0)
        rotate(astack);
    else if (ft_strncmp(line, "rb", 2) == 0)
        rotate(bstack);
    else if (ft_strncmp(line, "rr", 2) == 0)
        do_rr(astack, bstack);
    else if (ft_strncmp(line, "rra", 3) == 0)
        reverse_rotate(astack);
    else if (ft_strncmp(line, "rrb", 3) == 0)
        reverse_rotate(bstack);
    else if (ft_strncmp(line, "rrr", 3) == 0)
        do_rrr(astack, bstack);
}

int	main(int argc, char **argv)
{
	t_stack	*a_stack;
	t_stack	*b_stack;

	a_stack = NULL;
	b_stack = NULL;
	if (!check_inputs(argc, argv))
	{
		write(2, "Error\n", 6);
		return (1);
	}
	process_args(argv, &a_stack);
	if (check_stack(&a_stack))
	{
		write(2, "Error\n", 6);
		free_stack(a_stack);
		return (1);
	}
    process_instructions(&a_stack, &b_stack);
    if (is_sorted(a_stack) && !b_stack)
        write(1, "OK\n", 3);
    else
        write(1, "KO\n", 3);
    free_stack(a_stack);
	free_stack(b_stack);
	return (0);
}
