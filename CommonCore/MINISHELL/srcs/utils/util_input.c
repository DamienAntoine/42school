#include "../../headers/minishell.h"

char	**prepare_full_args(t_command *cmdtable, int *arg_count)
{
	int		i;
	char	**full_args;

	i = 0;
	*arg_count = 0;
	while (cmdtable->args[*arg_count] != NULL)
		(*arg_count)++;
	full_args = malloc((*arg_count + 2) * sizeof(char *));
	if (!full_args)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	full_args[0] = cmdtable->cmds;
	while (i < *arg_count)
	{
		full_args[i + 1] = cmdtable->args[i];
		i++;
	}
	full_args[*arg_count + 1] = NULL;
	return (full_args);
}
