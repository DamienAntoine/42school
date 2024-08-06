#include "../headers/philosophers.h"

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

void	better_usleep(long long time, t_data *data)
{
	long long	start_time;
	t_philo		*philo;

	start_time = gettime_ms(data);
	philo = data->philos;
	while ((gettime_ms(data) - start_time) < time)
	{
		if (data->death_flag)
		{
			if (philo->is_holding_forks == 1)
				drop_fork(philo);
			return ;
		}
		usleep(100);
	}
}

int	checkinputs(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (ft_isdigit(argv[i][j]) != 1)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
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

long long	ft_atoll(const char *str)
{
	long long	result;
	int			sign;

	result = 0;
	sign = 1;
	while (*str <= 32)
	{
		str++;
	}
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (sign * result);
}
