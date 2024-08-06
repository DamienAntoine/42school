#include "../headers/philosophers.h"

void	take_fork(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (data->death_flag || data->eat_max_flag)
		return ;
	if (philo->id == data->philo_nb)
	{
		pthread_mutex_lock(&data->forks[philo->id - 1]);
		pthread_mutex_lock(&data->forks[0]);
	}
	else
	{
		pthread_mutex_lock(&data->forks[philo->id - 1]);
		pthread_mutex_lock(&data->forks[(philo->id)]);
	}
	philo->is_holding_forks = 1;
	if (data->death_flag || data->eat_max_flag)
	{
		drop_fork(philo);
		return ;
	}
	print_actions(philo, FORKS);
}

void	drop_fork(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (philo->id == data->philo_nb)
	{
		pthread_mutex_unlock(&data->forks[0]);
		pthread_mutex_unlock(&data->forks[philo->id - 1]);
	}
	else
	{
		pthread_mutex_unlock(&data->forks[philo->id]);
		pthread_mutex_unlock(&data->forks[philo->id - 1]);
	}
	philo->is_holding_forks = 0;
}

void	eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (data->philo_nb < 2 || data->death_flag)
		return ;
	take_fork(philo);
	pthread_mutex_lock(data->w_lock);
	if (data->death_flag || data->eat_max_flag)
	{
		pthread_mutex_unlock(data->w_lock);
		if (philo->is_holding_forks == 1)
			drop_fork(philo);
		return ;
	}
	pthread_mutex_unlock(data->w_lock);
	eat_helper(philo, data);
}

void	eat_helper(t_philo *philo, t_data *data)
{
	philo->last_meal = gettime_ms(data);
	print_actions(philo, EAT);
	better_usleep(data->eatingtime, data);
	pthread_mutex_lock(data->w_lock);
	if (data->death_flag || data->eat_max_flag)
	{
		pthread_mutex_unlock(data->w_lock);
		if (philo->is_holding_forks == 1)
			drop_fork(philo);
		return ;
	}
	pthread_mutex_unlock(data->w_lock);
	drop_fork(philo);
	philo->next_to_eat = 0;
	philo->eat_counter++;
	if (philo->eat_counter == data->eat_max)
	{
		data->eat_max_flag = 1;
		return ;
	}
	philo_sleep(philo);
}
