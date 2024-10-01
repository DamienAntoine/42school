#include "../../headers/minishell.h"

// syntax: echo <flag> <string>
void	handle_flags(t_data *data, int *i, int *n_flag)
{
	while (data->commands->args[*i] && !ft_strcmp(data->commands->args[*i],
			"-n"))
	{
		*n_flag = 1;
		(*i)++;
	}
}

char	*ft_strcat(char *dest, const char *src)
{
	int	i;
	int	j;

	i = 0;
	while (dest[i] != '\0')
		i++;
	j = 0;
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

void	ft_strlcat_char(char *dst, char c, size_t dstsize)
{
	size_t	dst_len;

	dst_len = ft_strlen(dst);
	if (dst_len + 1 < dstsize)
	{
		dst[dst_len] = c;
		dst[dst_len + 1] = '\0';
	}
}



int	is_in_single_quote(const char *arg, int position)
{
	int	i;
	int	single_quotes;

	i = 0;
	single_quotes = 0;
	while (i < position)
	{
		if (arg[i] == '\'')
			single_quotes++;
		i++;
	}
	return (single_quotes % 2 != 0);
}

/*void	process_argument(char *arg, t_data *data)
{
	char	*processed_arg;
	char	*temp;
	char	*quote_buffer;
	int		i;
	int		start;
	char	quote_type;
	char	*expanded_content;
	size_t	buffer_size;
	size_t	curr_len;

	buffer_size = ft_strlen(arg) + 1;
	processed_arg = malloc(buffer_size);
	if (!processed_arg)
		return ;
	processed_arg[0] = '\0';
	quote_buffer = NULL;
	i = 0;
	start = 0;
	while (arg[i])
	{
		if (is_quote(arg[i]))
		{
			quote_type = arg[i];
			if (i > start)
			{
				temp = ft_substr(arg, start, i - start);
				curr_len = ft_strlen(processed_arg) + ft_strlen(temp) + 1;
				if (curr_len > buffer_size)
				{
					buffer_size = curr_len;
					processed_arg = realloc(processed_arg, buffer_size);
				}
				if (quote_type == '\'')
					ft_strlcat(processed_arg, temp, buffer_size);
				else
				{
					expanded_content = process_double_quotes(temp, data);
					curr_len = ft_strlen(processed_arg)
						+ ft_strlen(expanded_content) + 1;
					if (curr_len > buffer_size)
					{
						buffer_size = curr_len;
						processed_arg = realloc(processed_arg, buffer_size);
					}
					ft_strlcat(processed_arg, expanded_content, buffer_size);
					free(expanded_content);
				}
				free(temp);
			}
			i++;
			start = i;
			quote_buffer = malloc(ft_strlen(arg) + 1);
			if (!quote_buffer)
			{
				free(processed_arg);
				return ;
			}
			quote_buffer[0] = '\0';
			while (arg[i] && arg[i] != quote_type)
			{
				temp = ft_substr(arg, i, 1);
				curr_len = ft_strlen(quote_buffer) + 1;
				if (curr_len > buffer_size)
				{
					buffer_size = curr_len;
					quote_buffer = realloc(quote_buffer, buffer_size);
				}
				ft_strlcat(quote_buffer, temp, buffer_size);
				free(temp);
				i++;
			}
			curr_len = ft_strlen(processed_arg) + ft_strlen(quote_buffer) + 1;
			if (curr_len > buffer_size)
			{
				buffer_size = curr_len;
				processed_arg = realloc(processed_arg, buffer_size);
			}
			if (quote_type == '\'')
				ft_strlcat(processed_arg, quote_buffer, buffer_size);
			else if (quote_type == '\"')
			{
				expanded_content = process_double_quotes(quote_buffer, data);
				curr_len = ft_strlen(processed_arg)
					+ ft_strlen(expanded_content) + 1;
				if (curr_len > buffer_size)
				{
					buffer_size = curr_len;
					processed_arg = realloc(processed_arg, buffer_size);
				}
				ft_strlcat(processed_arg, expanded_content, buffer_size);
				free(expanded_content);
			}
			free(quote_buffer);
			start = ++i;
		}
		else
			i++;
	}
	temp = ft_substr(arg, start, i - start);
	if (is_in_single_quote(arg, start))
	{
		curr_len = ft_strlen(processed_arg) + ft_strlen(temp) + 1;
		if (curr_len > buffer_size)
		{
			buffer_size = curr_len;
			processed_arg = realloc(processed_arg, buffer_size);
		}
		ft_strlcat(processed_arg, temp, buffer_size);
	}
	else
	{
		expanded_content = process_double_quotes(temp, data);
		curr_len = ft_strlen(processed_arg) + ft_strlen(expanded_content) + 1;
		if (curr_len > buffer_size)
		{
			buffer_size = curr_len;
			processed_arg = realloc(processed_arg, buffer_size);
		}
		ft_strlcat(processed_arg, expanded_content, buffer_size);
		free(expanded_content);
	}
	free(temp);
	print_escape(processed_arg);
	free(processed_arg);
}*/

void	print_escape(char *arg)
{
	int	j;

	j = 0;
	while (arg[j])
	{
		if (arg[j] == '\\' && arg[j + 1])
		{
			j++;
			if (arg[j] == 'n')
				ft_putchar_fd('\n', 1);
			else if (arg[j] == 't')
				ft_putchar_fd('\t', 1);
			else if (arg[j] == '\\')
				ft_putchar_fd('\\', 1);
			else if (arg[j] == '\'')
				ft_putchar_fd('\'', 1);
			else if (arg[j] == '\"')
				ft_putchar_fd('\"', 1);
			else
				ft_putchar_fd(arg[j], 1);
		}
		else
			ft_putchar_fd(arg[j], 1);
		j++;
	}
}

int	ft_echo(t_data *data)
{
	int		n_flag;
	int		i;
	char	*arg;

	n_flag = 0;
	i = 0;
	handle_flags(data, &i, &n_flag);
	while (data->commands->args[i])
	{
		arg = data->commands->args[i];
		//process_argument(arg, data);
		print_escape(arg);
		if (data->commands->args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (!n_flag)
		ft_putchar_fd('\n', 1);
	data->state.last_exit_status = 0;
	return (0);
}
