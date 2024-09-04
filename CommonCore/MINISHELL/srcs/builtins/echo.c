#include "../../headers/minishell.h"
//syntax: echo <flag> <string>
//echo prints the string given as input with a newline at the end
//flag to implement : -n (prints the string without newline)
/*
void    ft_echo(t_token_list  *cur)//version printing from tokens
{
    int n_flag;
    int i;
    int size;

    n_flag = 0;
    i = 1;
    size = cur->token_count;

    if (size > 1)
    {
        while (cur->tokens[i] && !ft_strcmp(cur->tokens[i], "-n"))
        {
            n_flag = 1;
            i++;
        }
        while (cur->tokens[i] && ft_strcmp(cur->tokens[i], "|"))
        {
            ft_putstr_fd(cur->tokens[i], 1);
            if (cur->tokens[i + 1] && cur->tokens[i][0])
                ft_putchar_fd(' ', 1);
            i++;
        }
        if (n_flag == 0)
            ft_putchar_fd('\n', 1);
    }
}*/

void ft_echo(t_data *cur)//version with data to be able to print from commands->args (not working for some reason ?)
{
	int n_flag;
	int i;

	n_flag = 0;
	i = 0;
	while (cur->commands->args[i] && ft_strcmp(cur->commands->args[i], "-n") == 0)
	{
		n_flag = 1;
		i++;
	}
	while (cur->commands->args[i])
	{
		ft_putstr_fd(cur->commands->args[i], 1);
		if (cur->commands->args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (!n_flag)
		ft_putchar_fd('\n', 1);
}


/*

    // Check for the "-n" flag
    if (current->args[i] && !ft_strcmp(current->args[i], "-n"))
    {
        n_flag = 1;
        i++;
    }

    // Print each argument
    while (current->args[i])
    {
        ft_putstr_fd(current->args[i], 1);
        if (current->args[i + 1])
            ft_putchar_fd(' ', 1);  // Add space between arguments
        i++;
    }

    // If "-n" flag is not set, add a newline
    if (!n_flag)
        ft_putchar_fd('\n', 1);

*/
