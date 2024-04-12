#include "../includes/minitalk.h"

void    signal_handler(int c)
{

}

int main(int argc, char **argv)
{
    int pid;

    if (argc != 1)
    {
        ft_printf("Incorrect number of arguments");
        return (0);
    }
    pid = getpid();
    ft_printf("PID: %d", pid);
    while (argc == 1)
    {
        signal(SIGUSR1, ft_handler);
        signal(SIGUSR2, ft_handler);
        pause();
    }
    return (0);
}