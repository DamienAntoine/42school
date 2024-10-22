#include "../../headers/minishell.h"

int	open_redirection(t_redirection *redir)
{
	int	fd;

	fd = -1;
	if (redir->type == 0)
		fd = open(redir->file, O_RDONLY);
	else if (redir->type == 1)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == 2)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (redir->type == 3)
		fd = handle_here_doc(redir);
	return (fd);
}

int	setup_redirection(t_redirection *redir)
{
	int	fd;

	while (redir)
	{
		if (redir->type == 0)
		{
			fd = open_redirection(redir);
			if (dup2(fd, STDIN_FILENO) == -1)
			{
				close(fd);
				return (-1);
			}
			close(fd);
		}
		else if (redir->type == 1)
		{
			fd = open_redirection(redir);
			if (fd == -1)
				return (-1);
			if (dup2(fd, STDOUT_FILENO) == -1)
			{
				close(fd);
				return (-1);
			}
			close(fd);
		}
		else if (redir->type == 2)
		{
			fd = open_redirection(redir);
			if (fd == -1)
				return (-1);
			if (dup2(fd, STDOUT_FILENO) == -1)
			{
				close(fd);
				return (-1);
			}
			close(fd);
		}
		else if (redir->type == 3)
			handle_here_doc(redir);
		redir = redir->next;
	}
	return (0);
}

int	handle_here_doc(t_redirection *redir)
{
	char	*delimiter;
	char	*line;
	int		pipefd[2];

	delimiter = redir->file;
	line = NULL;
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}
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
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]);
	return (pipefd[0]);
}

void	add_redirection(t_command *current_command, char *file, int type)
{
	t_redirection	*new_redir;
	t_redirection	*tmp;

	new_redir = malloc(sizeof(t_redirection));
	if (!new_redir)
	{
		perror("Failed to allocate memory for new redirection");
		return ;
	}
	new_redir->file = ft_strdup(file);
	if (!new_redir->file)
	{
		free(new_redir);
		perror("Failed to duplicate file string");
		return ;
	}
	new_redir->type = type;
	new_redir->next = NULL;
	if (current_command->redirects == NULL)
		current_command->redirects = new_redir;
	else
	{
		tmp = current_command->redirects;
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
		}
		tmp->next = new_redir;
	}
}

void	ft_sortredirect(t_data *data, t_command *current_command, int *i)
{
	t_token_list	*toklist;
	int				redirect_type;

	toklist = data->toklist;
	redirect_type = -1;
	if (ft_strcmp(toklist->tokens[*i], "<") == 0)
		redirect_type = 0;
	else if (ft_strcmp(toklist->tokens[*i], ">") == 0)
		redirect_type = 1;
	else if (ft_strcmp(toklist->tokens[*i], ">>") == 0)
		redirect_type = 2;
	else if (ft_strcmp(toklist->tokens[*i], "<<") == 0)
		redirect_type = 3;
	if (redirect_type != -1)
	{
		(*i)++;
		if (*i < toklist->token_count)
			add_redirection(current_command, toklist->tokens[*i],
					redirect_type);
		else
			fprintf(stderr,
					"Syntax error: No file name after redirection operator.\n");
		(*i)++;
	}
}
