#include "../../headers/minishell.h"
//syntax: cd <path>
//should work with relative path (from current directory) and
//also with absolute path (from home directory)
void    cd(t_command *current)
{
    if (current->args[1])
    {
        printf("Too many args for cd command");
        return ;
    }
    if (!current->args[0])
        //move to home
    else if (!ft_strcmp(current->args[0], ".."))
        // move one up
    else (current->args[0])
        // move to this path(current->args[i])
}
