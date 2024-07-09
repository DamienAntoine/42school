#include "../headers/philosophers.h"

void	threads_create(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		philo[i].id = i + 1;
		philo[i].data = data;
		philo[i].eat_counter = 0;
		philo[i].data->death_flag = 0;
		if (pthread_create(&data->th[i], NULL, philo_actions,
				(void *)&philo[i]) != 0)
		{
			perror("Failed to create thread");
			free(philo);
			exit(1);
		}
		i++;
	}
}

void	monitor_create(t_data *data, t_philo *philo)
{
	pthread_t monitor;

	if (pthread_create(&monitor, NULL, monitor_routine, (void *)philo) != 0)
	{
		perror("Failed to create monitor thread");
		exit(1);
	}
	pthread_detach(monitor);
}

void	threads_join(t_data *data)
{
	int i;

	i = 0;
	while (i < data->philo_nb)
	{
		if (pthread_join(data->th[i], NULL) != 0)
			exit(2);
		i++;
	}
}
