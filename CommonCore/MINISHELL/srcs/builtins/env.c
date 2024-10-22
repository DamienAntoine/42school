#include "../../headers/minishell.h"

int	ft_env(t_env *lst)
{
	while (lst)
	{
		if (lst->value && *lst->value)
		{
			ft_putstr_fd(lst->type, 1);
			ft_putchar_fd('=', 1);
			ft_putstr_fd(lst->value, 1);
			ft_putchar_fd('\n', 1);
		}
		lst = lst->next;
	}
	return (0);
}

static void free_env_array(char **env_array, int count)
{
    while (count > 0)
        free(env_array[--count]);
    free(env_array);
}

static char *create_env_entry(t_env *temp)
{
    size_t len = ft_strlen(temp->type) + ft_strlen(temp->value) + 2;
    char *entry = malloc(len);

    if (!entry)
        return NULL;
    ft_strlcpy(entry, temp->type, len);
    ft_strlcat(entry, "=", len);
    ft_strlcat(entry, temp->value, len);
    return entry;
}

static int count_env_vars(t_env *env_list)
{
    int count;
    t_env *temp;

    count = 0;
    temp = env_list;
    while (temp)
    {
        count++;
        temp = temp->next;
    }
    return count;
}

char **env_list_to_array(t_env *env_list)
{
    int count;
    char **env_array;
    t_env *temp;
    int i;

    count = count_env_vars(env_list);
    env_array = malloc(sizeof(char *) * (count + 1));
    if (!env_array)
        return NULL;
    temp = env_list;
    i = 0;
    while (temp)
    {
        env_array[i] = create_env_entry(temp);
        if (!env_array[i])
        {
            free_env_array(env_array, i);
            return NULL;
        }
        temp = temp->next;
        i++;
    }
    env_array[i] = NULL;
    return env_array;
}
