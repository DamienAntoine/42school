#include "../../headers/minishell.h"

void	free_env_list(t_env *env)
{
	t_env	*temp;

	while (env != NULL)
	{
		temp = env->next;
		if (env->type)
		{
			free(env->type);
			env->type = NULL;
		}
		if (env->value)
		{
			free(env->value);
			env->value = NULL;
		}
		free(env);
		env = temp;
	}
}

void	free_command(t_command *command)
{
	t_command	*temp;
	int			i;

	while (command)
	{
		i = 0;
		temp = command;
		if (command->args)
		{
			while (command->args[i])
			{
				free(command->args[i]);
				i++;
			}
			free(command->args);
		}
		if (command->cmds)
			free(command->cmds);
		free_redirections(command->redirects);
		command = command->next;
		free(temp);
	}
}

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_redirections(t_redirection *redirections)
{
	t_redirection	*temp;

	while (redirections)
	{
		temp = redirections;
		redirections = redirections->next;
		if (temp->heredoc_fd != -1)
		{
			close(temp->heredoc_fd);
			temp->heredoc_fd = -1;
		}
		if (temp->file)
		{
			free(temp->file);
			temp->file = NULL;
		}
		free(temp);
	}
}

void	free_token_list(t_token_list *token_list)
{
	if (token_list)
	{
		if (token_list->tokens)
			free_split(token_list->tokens);
		free(token_list);
	}
}
