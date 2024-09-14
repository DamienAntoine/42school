#include "../../headers/minishell.h"

void free_env_list(t_env *env)
{
    t_env *temp;

    while (env != NULL)
    {
        temp = env->next;
        if (env->type)
            free(env->type);
        if (env->value)
            free(env->value);
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

	while (redirections)
	{
		temp = redirections;
		redirections = redirections->next;
		if (temp->file)
			free(temp->file);
		free(temp);
	}
}

void	free_token_list(t_token_list *token_list)
{
	if (token_list->tokens)
		free_split(token_list->tokens);
	free(token_list);
}

void	free_minishell(t_data *data)
{
	if (data->toklist)
	{
		free_token_list(data->toklist);
		printf("Freeing toklist: %p\n", (void *)data->toklist);
	}
	if (data->commands)
	{
		free_command(data->commands);
		printf("Freeing commands: %p\n", (void *)data->commands);
	}
	if (data->env)
	{
		free_env_list(data->env);
		printf("Freeing env: %p\n", (void *)data->env);
	}
	if (data->redirects)
	{
		printf("Freeing redirects: %p\n", (void *)data->redirects);
		free_redirections(data->redirects);
	}
	else
	{
		printf("Redirects is NULL\n"); //debugging (but this gets printed so redirect is set to null somewhere in the code ? it prevents it from being freed)
	}
	free(data);
	printf("Freeing data: %p\n", (void *)data);
}
