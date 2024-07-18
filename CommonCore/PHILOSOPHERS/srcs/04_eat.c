#include "../headers/philosophers.h"

void	take_fork(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
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
	//pthread_mutex_lock(data->d_lock);
	take_fork(philo); // lock 2 forks for current philo
	//printf("last meal: %lld\n\n", philo->last_meal);
    philo->last_meal = gettime_ms(data);
	//printf("new last meal: %lld\n\n", philo->last_meal);
	print_actions(philo, EAT);
	usleep(data->eatingtime * 1000);
	drop_fork(philo); // drops the 2 forks
    philo->next_to_eat = 0;
	philo->eat_counter++;
	if (philo->eat_counter == data->eat_max)
	{
        data->eat_max_flag = 1;
        print_actions(philo, END);
		return ;
	}
	//pthread_mutex_unlock(data->d_lock);
	philo_sleep(philo);

}
