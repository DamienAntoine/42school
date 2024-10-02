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



	// Step 1: Count the number of variables
	while (temp)
	{
		count++;
		temp = temp->next;
	}

	// Step 2: Allocate an array of strings
	env_array = (char **)malloc(sizeof(char *) * (count + 1));
	if (!env_array)
		return (NULL);

	// Step 3: Fill the array
	temp = env_list;
	while (temp)
	{
        len = ft_strlen(temp->type) + ft_strlen(temp->value) + 2;
		// Format each string as "name=value"
		env_array[i] = malloc(len);
		if (!env_array[i])
        {
            while (i > 0)
            {
                free(env_array[--i]);
            }
            free(env_array);
            return NULL;
        }
				// You should handle freeing previously allocated memory here
		ft_strlcpy(env_array[i], temp->type, len);
		ft_strlcat(env_array[i], "=", len);
		ft_strlcat(env_array[i], temp->value, len);
		i++;
		temp = temp->next;
	}
	env_array[i] = NULL; // Null-terminate the array

	return (env_array);
}
