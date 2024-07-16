#include "../headers/philosophers.h"

void	free_data(t_data *data)
{
	free(data->th);
	free(data->forks);
	free(data->print_lock);
	free(data->d_lock);
	free(data->philos);
	free(data);
}

// send all philo threads here
void	free_philo(t_philo *philo)
{
	free(philo->data);
	free(philo);
}
