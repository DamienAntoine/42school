#include "../headers/philosophers.h"

void	monitor_routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	int i;
	long long current_time;

	i = 0;
	while (1)
	{
		usleep(1000);
		current_time = gettime_ms();
		while (i < data->philo_nb)
		{
			pthread_mutex_lock(&data->meal_lock);
			if ((current_time - data->philos[i].last_meal) > data->deathtimer)
			{
				data->death_flag = 1;
				pthread_mutex_unlock(&data->meal_lock);
				printf("%lld | Philosopher %d died\n", current_time, data->philos[i].id);
				return ;
			}
			pthread_mutex_unlock(&data->meal_lock);
			i++;
		}
		if (data
	}
}
