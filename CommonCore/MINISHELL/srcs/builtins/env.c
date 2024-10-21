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

char	**env_list_to_array(t_env *env_list)
{
	int count = 0;
	t_env *temp = env_list;
	char **env_array;
	int i = 0;
    size_t  len;

	while (temp)
	{
		count++;
		temp = temp->next;
	}
	env_array = (char **)malloc(sizeof(char *) * (count + 1));
	if (!env_array)
		return (NULL);
	temp = env_list;
	while (temp)
	{
        len = ft_strlen(temp->type) + ft_strlen(temp->value) + 2;
		env_array[i] = malloc(len);
		if (!env_array[i])
        {
            while (i > 0)
                free(env_array[--i]);
            free(env_array);
            return NULL;
        }
		ft_strlcpy(env_array[i], temp->type, len);
		ft_strlcat(env_array[i], "=", len);
		ft_strlcat(env_array[i], temp->value, len);
		i++;
		temp = temp->next;
	}
	env_array[i] = NULL; 
	return (env_array);
}
