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