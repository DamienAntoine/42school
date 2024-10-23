#include "../../headers/minishell.h"

size_t	estimate_buffer_size(const char *str, t_data *data)
{
	size_t	size;
	int		i;
	int		start;
	char	*var_name;
	char	*expanded_var;

	size = ft_strlen(str) + 1;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			if (str[i] == '?')
			{
				size += 11;
				i++;
			}
			else
			{
				start = i;
				while (str[i] && (isalnum(str[i]) || str[i] == '_'))
					i++;
				var_name = ft_substr(str, start, i - start);
				expanded_var = expand_variable(var_name, data);
				size += ft_strlen(expanded_var);
				free(var_name);
				free(expanded_var);
			}
		}
		else
			i++;
	}
	return (size);
}
