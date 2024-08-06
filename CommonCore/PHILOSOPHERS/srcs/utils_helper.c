#include "../headers/philosophers.h"

void	start_timer(t_data *timer)
{
	gettimeofday(&timer->start, NULL);
}

int	ft_isdigit(int c)
{
	if ((c >= '0' && c <= '9'))
	{
		return (1);
	}
	return (0);
}
