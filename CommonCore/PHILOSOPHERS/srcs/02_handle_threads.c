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
		//philo[i].data->death_flag = 0;
		philo[i].last_meal = gettime_ms(data);
        if (i % 2 == 0)
            philo[i].next_to_eat = 0;
        else
            philo[i].next_to_eat = 1;
		if (pthread_create(&data->th[i], NULL, (void *)philo_actions,
				(void *)&philo[i]) != 0)
		{
			perror("Failed to create thread");
            free_data(data);
			exit(1);
		}
		i++;
	}
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
