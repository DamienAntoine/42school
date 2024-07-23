#include "../headers/philosophers.h"

void	free_data(t_data *data)
{
	free(data->th);
	free(data->forks);
	free(data->print_lock);
	free(data->d_lock);
    free(data->w_lock);
	free(data->philos);
	free(data);
}

// send all philo threads here
void	free_philo(t_philo *philo)
{
	free(philo->data);
	free(philo);
}

void	mutexes_destroy(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(data->d_lock);
	pthread_mutex_destroy(data->w_lock);
	pthread_mutex_destroy(data->print_lock);
}
