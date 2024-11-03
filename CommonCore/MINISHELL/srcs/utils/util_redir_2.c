/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_redir_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <dantoine@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 12:15:12 by dantoine          #+#    #+#             */
/*   Updated: 2024/11/03 12:15:13 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	check_access(t_redirection *redir)
{
	if (access(redir->file, F_OK) == -1)
	{
		ft_putstr_fd(redir->file, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (-1);
	}
	if (access(redir->file, R_OK) == -1)
	{
		ft_putstr_fd(redir->file, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		return (-1);
	}
	return (0);
}

int	handle_input_redirection(t_redirection *redir)
{
	int	fd;

	if (check_access(redir) == -1)
		return (-1);
	fd = open_redirection(redir);
	if (fd == -1)
	{
		perror(redir->file);
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}
