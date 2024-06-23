#include "../headers/fractol.h"

void	ft_putchar_fd(char c, int fd)
{
	if (fd < 0)
		return ;
	else
		write(fd, &c, 1);
}

void	ft_putstr(char *s, int fd)
{
	int	i;

	i = 0;
	if (s && fd >= 0)
	{
		while (s[i])
		{
			ft_putchar_fd(s[i], fd);
			i++;
		}
		ft_putstr("\n", fd);
	}
}
