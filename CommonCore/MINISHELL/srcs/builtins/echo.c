#include "../../headers/minishell.h"
//syntax: echo <flag> <string>
//echo prints the string given as input with a newline at the end
//flag to implement : -n (prints the string without newline)

void    ft_echo(t_command *current)
{
    int n_flag;
    int i;

    n_flag = 0;
    i = 0;

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
}