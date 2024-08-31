
#include "../../headers/minishell.h"

//syntax: export
//implemented with no options

/*displays a list of all environment variables that have been
marked for export to child processes initiated by the current shell session*/

/*Displaying Exported Variables:
Running export without any arguments lists
all the variables that have been exported,
meaning they are available to child processes.
This is useful for verifying which environment
variables have been configured for export.*/

//to undo export, do unset.

//  how to use export.
//      either   just       export
//      or                  export MY_VAR="hello"   command and one arg(name="value").  
//      it doesnt work like export MY_VAR hello 

void   print_export(t_env *env_list)
{
    t_env   *current;
    current = env_list;

    while (current)
    {
        ft_putstr_fd("declare -x ", 1);
        ft_putstr_fd(current->type, 1);

        if (current->value)
        {
            ft_putstr_fd("=\"", 1);
            ft_putstr_fd(current->value, 1);
            ft_putstr_fd("\"", 1);
        }
        ft_putchar_fd('\n', 1);
        current = current->next;
    }
}

void    export_with_arg(t_env **env_list, char *name, char *value)
{
    t_env   *current;
    current = *env_list;
 

    while (current)
    {
        if (!ft_strcmp(current->type, name))
        {
            // if the variable already exists, update its value
            free(current->value);
            current->value = ft_strdup(value);
            return ;
        }
        current = current->next;
    }

    // if the variabale doesn't exist, create a new node
    t_env *new;
    new = malloc(sizeof(t_env));
    new->type = ft_strdup(name);
    new->value = ft_strdup(value);
    new->next = *env_list;
    *env_list = new;
}
