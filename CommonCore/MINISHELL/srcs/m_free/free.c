#include "../../headers/minishell.h"

void	free_env_list(t_env *env)
{
	t_env	*tmp;

	while (env != NULL)
	{
		tmp = env;
		env = env->next;
		free(tmp->type);
		free(tmp->value);
		free(tmp);
	}
}

void	free_command(t_command *command)
{
	t_command	*temp;

	while (command)
	{
		temp = command;
		command = command->next;
		free(temp->cmds);
		if (temp->args)
		{
			for (int i = 0; temp->args[i]; ++i)
			{
				free(temp->args[i]);
			}
			free(temp->args);
		}
		free_redirections(temp->redirections);
		free(temp);
	}
}

void	free_redirections(t_redirection *redirections)
{
	t_redirection	*temp;

	while (redirections)
	{
		temp = redirections;
		redirections = redirections->next;
		free(temp->file);
		free(temp);
	}
}

void	free_token_list(t_token_list *token_list)
{
	if (token_list)
	{
		if (token_list->tokens)
		{
			for (int i = 0; i < token_list->token_count; ++i)
			{
				free(token_list->tokens[i]);
			}
			free(token_list->tokens);
		}
		free(token_list);
	}
}