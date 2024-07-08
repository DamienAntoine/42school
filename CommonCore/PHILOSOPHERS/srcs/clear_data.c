#include "../headers/philosophers.h"

void	free_data(t_data *data)
{
	free(data->th);
	free(data->forks);
	free(data->w_lock);
	free(data->d_lock);
	free(data->meal_lock);
	free(data);
}

// send all philo threads here
void	free_philo(t_philo *philo)
{
	free(philo->data);
	free(philo->eat_counter);
	free(philo->id);
	free(philo);
}
