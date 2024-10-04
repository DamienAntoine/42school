#include "../../headers/minishell.h"

void free_env_list(t_env *env)
{
    t_env *temp;

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

	if (redirections)
	{
		while (redirections)
		{
			printf("%s\n", redirections->file);
			printf("%d\n", redirections->type);
			temp = redirections;
			redirections = redirections->next;
			if (temp->file)
			{
				free(temp->file);
				temp->file = NULL;
			}
			if (temp)
				free(temp);
		}
		free(redirections);
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

void	free_minishell(t_data *data)
{
	if (data->toklist)
		free_token_list(data->toklist);
	if (data->commands)
		free_command(data->commands);
	if (data->env)
		free_env_list(data->env);
	if (data->redirects != NULL)
	{
		free_redirections(data->redirects);
		data->redirects = NULL;
	}
	free(data);
}
