#include "../../headers/minishell.h"

void    ft_env(t_env *lst)
{
    while (lst)
    {
        if (lst->value)
        {
            ft_putstr_fd(lst->type, 1);
            ft_putchar_fd('=', 1);
            ft_putstr_fd(lst->value, 1);
            ft_putchar_fd('\n', 1);
        }
        lst = lst->next;
    }
}