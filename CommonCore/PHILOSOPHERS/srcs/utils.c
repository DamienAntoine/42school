#include "../headers/philosophers.h"

void	start_timer(t_data *timer)
{
	gettimeofday(&timer->start, NULL);
}

long long	gettime_ms(t_data *timer)
{
	struct timeval	currenttime;
	long long		sec;
	long long		usec;

	gettimeofday(&currenttime, NULL);
	sec = currenttime.tv_sec - timer->start.tv_sec;
	usec = currenttime.tv_usec - timer->start.tv_usec;
	return (sec * 1000LL + usec / 1000);
}

void better_usleep(long long time, t_data *data)
{
    long long start_time = gettime_ms(data);
    t_philo *philo;

    philo = data->philos;
    while ((gettime_ms(data) - start_time) < time)
    {
        if (data->death_flag)
        {
            if (philo->is_holding_forks == 1)
                drop_fork(philo);
            return;
        }
        usleep(100);
    }
}


int	ft_atoi(const char *str)
{
	int	sign;
	int	result;
	int	i;

	sign = 1;
	result = 0;
	i = 0;
	while ((str[i] == 32) || (str[i] >= 9 && str[i] <= 13))
	{
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
		{
			sign *= -1;
		}
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (sign * result);
}
