#include "../headers/philosophers.h"

void	monitor_routine(void *arg)
{
	t_data		*data;
	int			i;
	long long	current_time;

	printf("\nentering monitor\n");
	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		current_time = gettime_ms(data);
		while (i < data->philo_nb)
		{
			// printf("\n\n");
			// printf("Monitoring Philosopher %d\n", data->philos[i].id);
			// printf("Current time: %lld\n", current_time);
			// printf("Last meal: %lld\n", data->philos[i].last_meal);
			// printf("Time remaining: %lld\n", current_time - data->philos[i].last_meal);
			// printf("\n\n");
			if ((current_time - data->philos[i].last_meal) > data->deathtimer)
			{
				pthread_mutex_lock(data->w_lock);
				data->death_flag = 1;
				pthread_mutex_unlock(data->w_lock);
				print_actions(&data->philos[i], DEAD);
				return ;
			}
			i++;
		}
		usleep(1000);
	}
	printf("\nExiting monitor\n");
}
