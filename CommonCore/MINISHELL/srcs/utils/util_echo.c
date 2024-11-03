/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhwang <sanhwang@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 12:17:40 by sanhwang          #+#    #+#             */
/*   Updated: 2024/11/03 15:49:02 by sanhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	handle_flags(t_data *data, int *i, int *n_flag)
{
	while (data->commands->args[*i] && !ft_strcmp(data->commands->args[*i],
			"-n"))
	{
		*n_flag = 1;
		(*i)++;
	}
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
