#include "../headers/philosophers.h"

void	monitor_routine(void *arg)
{
    printf("\nentering monitor\n");
	t_data	*data;

	data = (t_data *)arg;
	int i;
	long long current_time;

	i = 0;
	printf("eatingtime %d\n", data->eatingtime);
	printf("deathtimer %d\n", data->deathtimer);
	while (1)
	{
		usleep(100);
		current_time = gettime_ms();
		while (i < data->philo_nb)
		{
			pthread_mutex_lock(data->d_lock);
			if ((current_time - data->philos[i].last_meal) > data->deathtimer)
			{
				data->death_flag = 1;
				pthread_mutex_unlock(data->d_lock);
                pthread_mutex_lock(data->print_lock);
				printf("%lld | Philosopher %d died\n", current_time, data->philos[i].id);
				pthread_mutex_unlock(data->print_lock);
                break ;
			}
			pthread_mutex_unlock(data->d_lock);
			i++;
		}
        printf("deadflag: %d\n", data->death_flag);
        if (data->death_flag == 1 || data->eat_max_flag == 1)
                break ;
	}
    printf("\nExiting monitor\n");
}

