#include "../../headers/minishell.h"

void    env(t_env *lst)
{
    while (lst)
    {
        if (lst->value)
            printf("%s=%s\n", lst->type, lst->value);
        lst = lst->next;
    }
}
