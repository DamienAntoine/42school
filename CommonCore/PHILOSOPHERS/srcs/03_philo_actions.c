#include "../headers/philosophers.h"

// eat, sleep, if not eating and not sleeping, think
// deathtimer starts at the start of program and resets when philo starts eating
// if philo doesnt eat until deathtimer is reached, end
// find a way to create a countdown for deathtimer

void	philo_actions(t_philo *philo)
{
	t_data	*data;
	int		current_time;

	//&data->forks[philo->id] = fourchette correspondant au philo
	// data->philo_nb = last philo
	// philo with even IDs eat first
	// start by sending philos to eat, others think
	// philos done eating go sleep, philos thinking go eat
	// repeat
	// find a way to tell the program a philosopher is done eating so the others can start
	data = philo->data;
	while (data->death_flag == 0)
	{
		if (philo->id % 2 == 0)
		{
			eat(philo);
		}
		else if (philo->id % 2 != 0)
		{
			think(philo);
		}
		current_time = get_time_in_ms();
		if (current_time - philo->last_meal >= data->deathtimer)
		{
			pthread_mutex_lock(&data->d_lock);
			if (data->death_flag == 0)
			{
				data->death_flag = 1;
				ft_printf("%d | Philosopher %d died", current_time,
					philo->id);
			}
			pthread_mutex_unlock(&data->d_lock);
			break ;
		}
	}
}

void	think(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	ft_printf("%lf | Philosopher %d is thinking", gettime_ms(gettime_ms()),
		philo->id);
	// print Thinking when philosopher is queuing for a fork ?
	usleep(data->eatingtime);
	// Find a way for the philosophers to know when forks are available
}

void	philo_sleep(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	ft_printf("%lf | Philosopher %d is sleeping", gettime_ms(), philo->id);
	usleep(data->sleeptime);
}
