/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_redir_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <dantoine@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 12:14:43 by dantoine          #+#    #+#             */
/*   Updated: 2024/11/03 12:15:08 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	handle_output_redirection(t_redirection *redir)
{
	int	fd;

	if (access(redir->file, F_OK) == 0 && access(redir->file, W_OK) == -1)
	{
		ft_putstr_fd(redir->file, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		return (-1);
	}
	fd = open_redirection(redir);
	if (fd == -1)
	{
		perror(redir->file);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	setup_redirection(t_redirection *redir)
{
	int	result;

	result = 0;
	while (redir)
	{
		if (redir->type == 0)
			result = handle_input_redirection(redir);
		else if (redir->type == 1 || redir->type == 2)
			result = handle_output_redirection(redir);
		else if (redir->type == 3)
		{
			result = handle_here_doc(redir);
			if (result == -1)
				return (-1);
		}
		if (result == -1)
			return (-1);
		redir = redir->next;
	}
	return (0);
}

int	write_line_to_fd(const char *line, int write_fd)
{
	if (write(write_fd, line, ft_strlen(line)) == -1 || write(write_fd, "\n",
			1) == -1)
		return (-1);
	return (0);
}

int	process_heredoc_lines(const char *delimiter, int write_fd)
{
	char	*line;

	if (write_fd < 0)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			ft_putstr_fd("\n", STDERR_FILENO);
			break ;
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		if (write_line_to_fd(line, write_fd) == -1)
		{
			free(line);
			return (-1);
		}
		free(line);
	}
	return (0);
}

int	handle_here_doc(t_redirection *redir)
{
	if (redir->heredoc_fd < 0)
		return (-1);
	if (dup2(redir->heredoc_fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		return (-1);
	}
	close(redir->heredoc_fd);
	redir->heredoc_fd = -1;
	return (0);
}
