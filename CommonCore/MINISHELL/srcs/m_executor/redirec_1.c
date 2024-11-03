/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <dantoine@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 12:12:13 by dantoine          #+#    #+#             */
/*   Updated: 2024/11/03 12:12:14 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	check_heredoc(int redirect_type, t_token_list *toklist, int *i)
{
	if (redirect_type == 3)
	{
		if (ft_strncmp(toklist->tokens[*i], "<<<", 3) == 0)
			return (-1);
		if (*i + 1 < toklist->token_count)
		{
			if (ft_strcmp(toklist->tokens[*i + 1], "<<") == 0
				|| ft_strcmp(toklist->tokens[*i + 1], "<") == 0
				|| ft_strcmp(toklist->tokens[*i + 1], ">") == 0
				|| ft_strcmp(toklist->tokens[*i + 1], ">>") == 0)
				return (-1);
		}
		if (*i + 1 >= toklist->token_count
			|| toklist->tokens[*i + 1][0] == '\0')
			return (-1);
	}
	return (0);
}

int	get_redirect_type(const char *token)
{
	if (ft_strcmp(token, "<") == 0)
		return (0);
	else if (ft_strcmp(token, ">") == 0)
		return (1);
	else if (ft_strcmp(token, ">>") == 0)
		return (2);
	else if (ft_strcmp(token, "<<") == 0)
		return (3);
	return (-1);
}

int	handle_redirection_error(t_data *data)
{
	fprintf(stderr, "Syntax error: No file name after redirection operator.\n");
	set_exit_status(2, data);
	return (-1);
}

int	ft_sortredirect(t_data *data, t_command *current_command, int *i)
{
	t_token_list	*toklist;
	int				redirect_type;

	toklist = data->toklist;
	redirect_type = get_redirect_type(toklist->tokens[*i]);
	if (redirect_type != -1)
	{
		if (check_heredoc(redirect_type, toklist, i) == -1)
		{
			fprintf(stderr, "Syntax error: Invalid heredoc syntax.\n");
			set_exit_status(2, data);
			return (-1);
		}
		(*i)++;
		if (*i < toklist->token_count)
			add_redirection(current_command, toklist->tokens[*i],
				redirect_type);
		else
			return (handle_redirection_error(data));
		(*i)++;
	}
	return (0);
}

// int	ft_sortredirect(t_data *data, t_command *current_command, int *i)
// {
// 	t_token_list	*toklist;
// 	int				redirect_type;

// 	toklist = data->toklist;
// 	redirect_type = get_redirect_type(toklist->tokens[*i]);
// 	if (redirect_type != -1)
// 	{
// 		if (check_heredoc(redirect_type, toklist, i) == -1)
// 		{
// 			fprintf(stderr, "Syntax error: Invalid heredoc syntax.\n");
// 			set_exit_status(2, data);
// 			return (-1);
// 		}
// 		(*i)++;
// 		if (*i < toklist->token_count)
// 			add_redirection(current_command, toklist->tokens[*i],
// 				redirect_type);
// 		else
// 		{
// 			fprintf(stderr,
// 				"Syntax error: No file name after redirection operator.\n");
// 			set_exit_status(2, data);
// 			return (-1);
// 		}
// 		(*i)++;
// 	}
// 	return (0);
// }

// int	ft_sortredirect(t_data *data, t_command *current_command, int *i)
// {
// 	t_token_list	*toklist;
// 	int				redirect_type;

// 	toklist = data->toklist;
// 	redirect_type = -1;
// 	if (ft_strcmp(toklist->tokens[*i], "<") == 0)
// 		redirect_type = 0;
// 	else if (ft_strcmp(toklist->tokens[*i], ">") == 0)
// 		redirect_type = 1;
// 	else if (ft_strcmp(toklist->tokens[*i], ">>") == 0)
// 		redirect_type = 2;
// 	else if (ft_strcmp(toklist->tokens[*i], "<<") == 0)
// 		redirect_type = 3;
// 	if (redirect_type != -1)
// 	{
// 		if (check_heredoc(redirect_type, toklist, i) == -1)
// 		{
// 			fprintf(stderr, "Syntax error: Invalid heredoc syntax.\n");
// 			set_exit_status(2, data);
// 			return (-1);
// 		}
// 		(*i)++;
// 		if (*i < toklist->token_count)
// 			add_redirection(current_command, toklist->tokens[*i],
// 				redirect_type);
// 		else
// 		{
// 			fprintf(stderr,
// 				"Syntax error: No file name after redirection operator.\n");
// 			set_exit_status(2, data);
// 			return (-1);
// 		}
// 		(*i)++;
// 	}
// 	return (0);
// }
