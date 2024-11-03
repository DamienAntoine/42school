/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhwang <sanhwang@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 12:12:45 by dantoine          #+#    #+#             */
/*   Updated: 2024/11/03 14:22:04 by sanhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	handle_input(t_data *data)
{
	char	*input;

	input = get_full_input();
	if (!input)
	{
		free_minishell(data);
		return (0);
	}
	add_command_to_history(&(data->history), input);
	data->toklist->tokens = ft_tokenize(data, input);
	free(input);
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;

	(void)argv;
	if (argc > 1)
		exit(0);
	data = init_minishell(env);
	signal(SIGINT, handle_sigint);
	ignore_sigquit();
	rl_bind_key('\t', rl_insert);
	while (1)
	{
		reset_toklist(data);
		if (!handle_input(data))
			return (0);
		reset_command(data);
		set_exit_status(0, data);
		if (ft_sort_tokens(data) == -1 || data->state.last_exit_status != 0)
			continue ;
		signal(SIGINT, SIG_IGN);
		execute_command(data);
		signal(SIGINT, handle_sigint);
	}
	return (free_minishell(data), 0);
}
