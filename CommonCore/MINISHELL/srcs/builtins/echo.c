#include "../../headers/minishell.h"
//syntax: echo <flag> <string>
//echo prints the string given as input with a newline at the end
//flag to implement : -n (prints the string without newline)


// handle echo $?  for error status***************


void    ft_echo(t_token_list  *cur, t_state *state, t_env *lst)
{
    char    *env_type;
    char    *env_value;
    int n_flag;
    int i;
  
    n_flag = 0;
    i = 1;
  
    while (i < cur->token_count && !ft_strcmp(cur->tokens[i], "-n"))
    {
        n_flag = 1;
        i++;
    }

    while (i < cur->token_count)
    {
        if (!ft_strcmp(cur->tokens[i], "$?"))
            ft_putnbr_fd(state->last_exit_status, 1);
        else if (cur->tokens[i][0] == '$')
        {
            env_type = &cur->tokens[i][1];
            env_value = find_env_value(lst, env_type);
            if (env_value)
                ft_putstr_fd(env_value, 1);
        }
        else
            ft_putstr_fd(cur->tokens[i], 1);
        
        if (i + 1 < cur->token_count)
            ft_putchar_fd(' ', 1);
        i++;
    }

    if (!n_flag)
        ft_putchar_fd('\n', 1);
    state->last_exit_status = 0;  //echo usually succeeds
}