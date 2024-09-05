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

   if (command->args) {
        for (int i = 0; command->args[i]; i++)
            free(command->args[i]);
        free(command->args);
    }
    free(command->cmds);
    free(command);
/*
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
*/

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
    free(token_list->tokens);
}
void	free_minishell(t_data *data)
{
	free_token_list(data->toklist);
	//free_redirections(data->redirects);
	free_command(data->commands);
	free_env_list(data->env);
	free(data);
}
