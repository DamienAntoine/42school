#include "../../headers/minishell.h"

void ignore_sigquit()
{
    struct sigaction sa;
    sa.sa_handler = SIG_IGN; // Ignore SIGQUIT
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGQUIT, &sa, NULL) == -1)
        perror("Failed to ignore SIGQUIT");
}


void setup_terminal()
{
    struct termios tio;
    if (tcgetattr(STDIN_FILENO, &tio) != 0)
	{
        perror("Failed to get terminal attributes");
        return;
    }

    tio.c_lflag &= ~ECHOCTL; // Disable control characters echoing

    if (tcsetattr(STDIN_FILENO, TCSANOW, &tio) != 0)
        perror("Failed to set terminal attributes");
} 

void	handle_sigint(int sig)
{
	(void)sig;
	ft_putstr_fd("\n\033[35mMSL> \033[0m", 1);
}

