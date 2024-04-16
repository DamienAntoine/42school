#include "../headers/minitalk.h"

void    signal_sender(int pid, char c, int client_pid)
{
        int     i;

        i = 0;
        while (i < 8)
        {
                if (c & (1 << i))
                {
                        kill(pid, SIGUSR1);
                }
                else
                        kill(pid, SIGUSR2);
                i++;
                usleep(1000);
        }
	while (1)
	{
		signal(SIGUSR1, signal_confirm);
		signal(SIGUSR2, signal_confirm);
		pause();
	}
}

void    signal_confirm(int c)
{
        static int      i;
        static int      letter;
        static int      init;

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
                        send_back(letter);
                        letter = 0;
                        i = 0;
                }
        }
}

void	send_clientpid(int client_pid)
{
	int     i;

        i = 0;
        while (i < 8)
        {
                if (c & (1 << i))
                {
                        kill(pid, SIGUSR1);
                }
                else
                        kill(pid, SIGUSR2);
                i++;
                usleep(1000);
        }
}

int	main(int argc, char **argv)
{
	int	pid;
	int	i;
	int	client_pid;

        client_pid = getpid();
	send_clientpid(client_pid);
	i = 0;
	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		while(argv[2][i])
		{
			signal_sender(pid, argv[2][i]);
			i++;
		}
		signal_sender(pid, '\n');
	}
	else
	{
		ft_printf("Incorrect number of arguments");
		return (1);
	}
	return (0);
}
