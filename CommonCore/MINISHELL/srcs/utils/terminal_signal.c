#include "../../headers/minishell.h"

void ignore_sigquit()
{
    struct sigaction sa;
    sa.sa_handler = SIG_IGN; 
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGQUIT, &sa, NULL) == -1)
        perror("Failed to ignore SIGQUIT");
}

void	handle_sigint(int sig)
{
	(void)sig;
	ft_putstr_fd("\n\033[35mMSL> \033[0m", 1);
}

