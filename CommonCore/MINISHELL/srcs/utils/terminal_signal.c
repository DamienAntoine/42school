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
	ft_putstr_fd("\033[2K\r", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
