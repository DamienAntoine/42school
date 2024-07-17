#include "../headers/philosophers.h"

void	take_fork(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (philo->id == data->philo_nb) // if last philo, take fork from first philo
	{
		pthread_mutex_lock(&data->forks[philo->id - 1]);
        printf("philo %d (last) took fork 1\n", philo->id);
		pthread_mutex_lock(&data->forks[1]);
        printf("philo %d (last) took fork 2\n", philo->id);
	}
	else
	{
		pthread_mutex_lock(&data->forks[philo->id - 1]);
        printf("philo %d took fork 1\n", philo->id);
		pthread_mutex_lock(&data->forks[(philo->id)]); // locks philo's fork + neighbour's fork
        printf("philo %d took fork 2\n", philo->id);
	}
    print_actions(philo, FORKS);
}

void	drop_fork(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (philo->id == data->philo_nb) // if last philo, drop fork from first philo
	{
        printf("philo %d trying to drop fork\n", philo->id);
		pthread_mutex_unlock(&data->forks[0]);
        printf("philo %d dropped fork 1\n", philo->id);
		pthread_mutex_unlock(&data->forks[philo->id]);
        printf("philo %d dropped fork 2\n", philo->id);
	}
	else
	{
		pthread_mutex_unlock(&data->forks[philo->id]);
        printf("philo %d dropped fork 1\n", philo->id);
		pthread_mutex_unlock(&data->forks[philo->id - 1]); // unlocks philo's fork + neighbour's fork
        printf("philo %d dropped fork 2\n", philo->id);
	}
}

void	eat(t_philo *philo)
{
	t_data	*data;

    data = philo->data;
	take_fork(philo); // lock 2 forks for current philo
    philo->last_meal = gettime_ms();
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
	philo_sleep(philo);
}
