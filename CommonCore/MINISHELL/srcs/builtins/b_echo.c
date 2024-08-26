#include "../../headers/minishell.h"
//syntax: echo <flag> <string>
//echo prints the string given as input with a newline at the end
//flag to implement : -n (prints the string without newline)
void    echo(t_command *current)
{
    int n_flag;
    int i;
    n_flag = 0;
    i = 0;

    blabla:

    if (!ft_strcmp(current->args[i], "-n"))
    {
        n_flag = 1;
        i++;testsetsetse
    }
    while (current->args[i])
        printf("%s",current->args[i++]);
    if (!n_flag)
        printf("\n");
}
