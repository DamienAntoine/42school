#include "../../headers/minishell.h"

char	*fin_input(char *input)
{
	char	*processed_input;

	processed_input = trim_input(input);
	return (processed_input);
}

char	**tokenize_input(char *processed_input)
{
	char	**args;
	char	*token;
	char	*dup;
	int		i;

	args = malloc(MAX_ARGS * sizeof(char *));
	if (!args)
		return (NULL);
	i = 0;
	token = ft_strtok(processed_input, " \t\n");
	while (token && i < MAX_ARGS - 1)
	{
		dup = ft_strdup(token);
		if (token != processed_input && strchr("<>|", *token))
			free(token);
		args[i++] = dup;
		token = ft_strtok(NULL, " \t\n");
	}
	args[i] = NULL;
	return (args);
}

char	**process_and_tokenize_input(char *input)
{
	char	*final_input;
	char	**args;

	final_input = fin_input(input);
	if (!final_input)
		return (NULL);
	args = tokenize_input(final_input);
	free(final_input);
	return (args);
}

// char	**process_and_tokenize_input(char *input)
// {
// 	char	**args;
// 	char	*processed_input;
// 	char	*token;
// 	char	*dup;
// 	int		i;

// 	processed_input = trim_input(input);
// 	if (!processed_input)
// 		return (NULL);
// 	args = malloc(MAX_ARGS * sizeof(char *));
// 	if (!args)
// 	{
// 		free(processed_input);
// 		return (NULL);
// 	}
// 	i = 0;
// 	token = ft_strtok(processed_input, " \t\n");
// 	while (token && i < MAX_ARGS - 1)
// 	{
// 		dup = ft_strdup(token);
// 		if (token != processed_input && strchr("<>|", *token))
// 			free(token);
// 		args[i++] = dup;
// 		token = ft_strtok(NULL, " \t\n");
// 	}
// 	args[i] = NULL;
// 	free(processed_input);
// 	return (args);
// }

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
		if (args[i] != expanded)
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
	return (handle_and_expand_tokens(data, args));
}
