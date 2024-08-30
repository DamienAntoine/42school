#include "../../headers/minishell.h"

void    ft_env(t_env *lst)
{
    while (lst)
    {
        if (lst->value)
            printf("%s=%s\n", lst->type, lst->value);
        lst = lst->next;
    }
}
