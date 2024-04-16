#include "../headers/minitalk.h"

void    signal_handler(int c)
{
	static int	i;
	static int	letter;
	static int	init;

	if (init != 1)
	{
		i = 0;
		letter = 0;
		init = 1;
	}
	if (c == SIGUSR1 || c == SIGUSR2)
	{
		if (c == SIGUSR1)
			letter |= (1 << i);
		i++;
		if (i == 8)
		{
			ft_printf("%c", letter);
			letter = 0;
			i = 0;
		}
	}
}

int main(int argc, char **argv)
{
    int pid;

    (void)argv;
    if (argc != 1)
    {
        ft_printf("Incorrect number of arguments");
        return (0);
    }
    pid = getpid();
    ft_printf("PID: %d\n", pid);
    while (1)
    {
        signal(SIGUSR1, signal_handler);
        signal(SIGUSR2, signal_handler);
        pause();
    }
    return (0);
}
