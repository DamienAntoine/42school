#include "../headers/minitalk.h"

void    signal_sender(int pid, char c)
{
	int	i;

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
		usleep(500);
	}
}

int main(int argc, char **argv)
{
    int pid;
    int i;

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
