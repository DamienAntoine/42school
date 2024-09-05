#include "../../headers/minishell.h"
//syntax: echo <flag> <string>
//echo prints the string given as input with a newline at the end
//flag to implement : -n (prints the string without newline)


// handle echo $?  for error status***************

void ft_echo(t_data *data)
{
    char    *env_type;
    char    *env_value;
    int     n_flag;
    int     i;

    n_flag = 0;
    i = 0;  // Start at index 0 since args[0] is the first argument

    // Loop to handle the "-n" flag
    while (data->commands->args[i] && !ft_strcmp(data->commands->args[i], "-n"))
    {
        n_flag = 1;
        i++;
    }

    // Loop through the command arguments
    while (data->commands->args[i])
    {
        // Handle the "$?" variable for exit status
        if (!ft_strcmp(data->commands->args[i], "$?"))
            ft_putnbr_fd(data->state.last_exit_status, 1);
        // Handle environment variables
        else if (data->commands->args[i][0] == '$')
        {
            env_type = &data->commands->args[i][1];
            env_value = find_env_value(data->env, env_type);  // Use data->env to find the variable
            if (env_value)
                ft_putstr_fd(env_value, 1);
        }
        // Print regular arguments
        else
            ft_putstr_fd(data->commands->args[i], 1);

        // Print space between arguments, but not after the last one
        if (data->commands->args[i + 1])
            ft_putchar_fd(' ', 1);
        i++;
    }

    // Print newline unless the "-n" flag is present
    if (!n_flag)
        ft_putchar_fd('\n', 1);

    // Set the last exit status to 0 since echo typically succeeds
    data->state.last_exit_status = 0;
}

/*
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
*/
