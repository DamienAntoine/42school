#include "../headers/minishell.h"

void free_env_list(t_env *env) 
{
    t_env *tmp;
    while (env != NULL) 
    {
        tmp = env;
        env = env->next;
        free(tmp->type);
        free(tmp->value);
        free(tmp);
    }
}
