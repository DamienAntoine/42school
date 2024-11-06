/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhwang <sanhwang@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 12:17:00 by sanhwang          #+#    #+#             */
/*   Updated: 2024/11/06 09:24:47 by sanhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ignore_sigquit(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		perror("Failed to ignore SIGQUIT");
}

void	handle_sigint(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_redisplay();
}
