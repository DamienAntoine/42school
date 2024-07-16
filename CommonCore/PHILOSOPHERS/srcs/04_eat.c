#include "../headers/philosophers.h"

void	take_fork(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (philo->id == data->philo_nb - 1) // if last philo, take fork from first philo
	{
		pthread_mutex_lock(&data->forks[philo->id]);
		pthread_mutex_lock(&data->forks[0]);
	}
	else
	{
		pthread_mutex_lock(&data->forks[philo->id]);
		pthread_mutex_lock(&data->forks[(philo->id) + 1]); // locks philo's fork + neighbour's fork
	}
    pthread_mutex_lock(data->print_lock);
	printf("%lld | Philosopher %d has taken a fork\n", gettime_ms(), philo->id);
    pthread_mutex_unlock(data->print_lock);
}

void	drop_fork(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (philo->id == data->philo_nb - 1) // if last philo, drop fork from first philo
	{
		pthread_mutex_unlock(&data->forks[0]);
		pthread_mutex_unlock(&data->forks[philo->id]);
	}
	else
	{
		pthread_mutex_unlock(&data->forks[(philo->id) + 1]);
		pthread_mutex_unlock(&data->forks[philo->id]); // unlocks philo's fork + neighbour's fork
	}
}

void	eat(t_philo *philo)
{
	t_data	*data;

    data = philo->data;
	take_fork(philo); // lock 2 forks for current philo
    pthread_mutex_lock(data->print_lock);
    philo->last_meal = gettime_ms();
	printf("%lld | Philosopher %d is eating\n", gettime_ms(), philo->id);
    pthread_mutex_unlock(data->print_lock);
	usleep(data->eatingtime);
	drop_fork(philo); // drops the 2 forks
    philo->next_to_eat = 0;
	philo->eat_counter++;
	if (philo->eat_counter == data->eat_max)
	{
        data->eat_max_flag = 1;
        pthread_mutex_lock(data->print_lock);
		printf("%lld | Target reached, end of simulation.\n", gettime_ms());
        pthread_mutex_unlock(data->print_lock);
		return ;
	}
	philo_sleep(philo);
}
