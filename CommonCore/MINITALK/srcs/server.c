#include "../headers/minitalk.h"

void    signal_handler(int c)
{
    int     i;
    char    letter;
    
    i = 7;
	letter = 0;
    while (i >= 0)
    {
        if (c & (1 << i))
            letter |= (1 << i);
        i--;
    }
    ft_printf("%c", letter);
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
