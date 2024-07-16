#include "../headers/philosophers.h"

// eat, sleep, if not eating and not sleeping, think
// deathtimer starts at the start of program and resets when philo starts eating
// if philo doesnt eat until deathtimer is reached, end
// find a way to create a countdown for deathtimer

void	philo_actions(t_philo *philo)
{
	t_data	*data;

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
        //odd philos start by thinking, so even philos can start by eating
        if (philo->next_to_eat == 1)
            eat(philo);//eat and sleep
		else if (philo->next_to_eat == 0)
			think(philo);//queue for fork
        // printf("\ninfinite loop test : philo id:%d, deathflag status: %d\n\n", philo->id, data->death_flag);
		if (data->death_flag == 1 || data->eat_max_flag == 1)
            return ;
	}
}

void	think(t_philo *philo)
{
	//t_data	*data;

	//data = philo->data;
    philo->next_to_eat = 1;
    pthread_mutex_lock(data->print_lock);
	printf("%lld | Philosopher %d is thinking\n", gettime_ms(),
		philo->id);
    pthread_mutex_unlock(data->print_lock);
	usleep(100);//wait 1ms so the other threads have time to lock their forks
}

void	philo_sleep(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
    philo->data->sleepflag = 1;
    pthread_mutex_lock(data->print_lock);
	printf("%lld | Philosopher %d is sleeping\n", gettime_ms(), philo->id);
    pthread_mutex_unlock(data->print_lock);
	usleep(data->sleeptime);
    return ;
}
