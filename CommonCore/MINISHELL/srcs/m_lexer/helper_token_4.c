#include "../../headers/minishell.h"

char	**process_and_tokenize_input(char *input)
{
	char			**args;
	char			*processed_input;
	char			*token;
	int				i;

	processed_input = trim_input(input);
	if (!processed_input)
		return (NULL);
	args = malloc(MAX_ARGS * sizeof(char *));
	if (!args)
	{
		free(input);
		return (NULL);
	}
	i = 0;
	token = ft_strtok(processed_input, " \t\n");
	while (token && i < MAX_ARGS - 1)
	{
		args[i++] = ft_strdup(token);
		token = ft_strtok(NULL, " \t\n");
	}
	args[i] = NULL;
	free(processed_input);
	return (args);
}

char	**handle_and_expand_tokens(t_data *data, char **args)
{
	t_token_list	*toklist;
	char			*expanded;
	int				i;

	toklist = data->toklist;
	i = 0;
	while (args[i])
	{
		expanded = handle_quotes(args[i], data);
		free(args[i]);
		args[i] = expanded;
		i++;
	}
	toklist->token_count = i;

	return (args);
}

char	**ft_tokenize(t_data *data, char *input)
{
	char	**args;

	args = process_and_tokenize_input(input);
	if (!args)
		return (NULL);

	return handle_and_expand_tokens(data, args);
}
