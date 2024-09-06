#include "../../headers/minishell.h"

void	free_env_list(t_env *env)
{
	t_env	*temp;

	while (env != NULL)
	{
		temp = env->next;
		free(env->type);
		free(env->value);
		free(env);
		env = temp;
	}
}

void	free_command(t_command *command)
{
	int	i;

	i = 0;
	if (command->args)
	{
		while (command->args[i])
		{
			free(command->args[i]);
			i++;
		}
		free(command->args);
	}
	free(command->cmds);
	free(command);
}

void	free_split(char **split)
{
	int	i;

	if (!split)
		return;
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
		free(temp->file);
		free(temp);
	}
}

void	free_token_list(t_token_list *token_list)
{
	free_split(token_list->tokens);
	free(token_list);
}

void	free_minishell(t_data *data)
{
	 if (data->toklist)
		free_token_list(data->toklist);
	if (data->commands)
		free_command(data->commands);
	if (data->env)
		free_env_list(data->env);
	if (data->redirects)
		free_redirections(data->redirects);
	free(data);
}
