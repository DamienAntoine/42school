#include "../headers/philosophers.h"

void	take_fork(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (data->death_flag)
		return ;
	if (philo->id == data->philo_nb) // if last philo, take fork from first philo
	{
		pthread_mutex_lock(&data->forks[philo->id - 1]);
		pthread_mutex_lock(&data->forks[0]);
	}
	else
	{
		pthread_mutex_lock(&data->forks[philo->id - 1]);
		pthread_mutex_lock(&data->forks[(philo->id)]); // locks philo's fork + neighbour's fork
	}
	print_actions(philo, FORKS);
}

void	drop_fork(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (data->death_flag)
		return ;
	if (philo->id == data->philo_nb) // if last philo, drop fork from first philo
	{
		pthread_mutex_unlock(&data->forks[0]);
		pthread_mutex_unlock(&data->forks[philo->id - 1]);
	}
	else
	{
		pthread_mutex_unlock(&data->forks[philo->id]);
		pthread_mutex_unlock(&data->forks[philo->id - 1]); // unlocks philo's fork + neighbour's fork
	}
}

void	eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (data->philo_nb < 2 || data->death_flag)
		return ;
	take_fork(philo); // lock 2 forks for current philo
	pthread_mutex_lock(data->w_lock);
	/*if (data->death_flag == 1)
	{
		pthread_mutex_unlock(data->w_lock);
		drop_fork(philo);
		return ;
	}*/
	pthread_mutex_unlock(data->w_lock);
	philo->last_meal = gettime_ms(data);
	print_actions(philo, EAT);
	better_usleep(data->eatingtime, data);
	pthread_mutex_lock(data->w_lock);
	/*if (data->death_flag == 1)
	{
		pthread_mutex_unlock(data->w_lock);
		drop_fork(philo);
		return ;
	}*/
	pthread_mutex_unlock(data->w_lock);
	drop_fork(philo); // drops the 2 forks
	philo->next_to_eat = 0;
	philo->eat_counter++;
	if (philo->eat_counter == data->eat_max)
	{
		data->eat_max_flag = 1;
		print_actions(philo, END);
		return ;
	}
	philo_sleep(philo);
}
