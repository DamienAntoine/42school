#include "../../headers/minishell.h"

int	handle_input_redirection(t_redirection *redir)
{
	int	fd;

	fd = open_redirection(redir);
	if (fd == -1)
		return (-1);
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	handle_output_redirection(t_redirection *redir)
{
	int	fd;

	fd = open_redirection(redir);
	if (fd == -1)
		return (-1);
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	setup_redirection(t_redirection *redir)
{
	int	result;

	while (redir)
	{
		if (redir->type == 0)
			result = handle_input_redirection(redir);
		else if (redir->type == 1 || redir->type == 2)
			result = handle_output_redirection(redir);
		else if (redir->type == 3)
			handle_here_doc(redir);
		if (result == -1)
			return (-1);
		redir = redir->next;
	}
	return (0);
}

int	process_heredoc_lines(const char *delimiter, int write_fd)
{
	char	*line;

	while (1)
	{
		line = readline("heredoc> ");
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
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
	return (0);
}

int	handle_here_doc(t_redirection *redir)
{
	char *delimiter;
	int pipefd[2];

	delimiter = redir->file;
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	if (process_heredoc_lines(delimiter, pipefd[1]) == -1)
	{
		close(pipefd[1]);
		return (-1);
	}
	close(pipefd[1]);
	return (pipefd[0]);
}