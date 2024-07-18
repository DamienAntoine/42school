#include "../headers/philosophers.h"

    // &data->forks[philo->id] = fourchette correspondant au philo
	// data->philo_nb = last philo
	// philo with even IDs eat first
	// start by sending philos to eat, others think
	// philos done eating go sleep, philos thinking go eat
	// repeat
	// find a way to tell the program a philosopher is done eating so the others can start
void    print_actions(t_philo *philo, int action)
{
    t_data  *data;
	long long int	cur_time;

    data = philo->data;
	cur_time = gettime_ms(data);
    pthread_mutex_lock(data->print_lock);
    if (action == EAT)
        printf("%lld | Philosopher %d is eating\n", cur_time, philo->id);
    if (action == SLEEP)
        printf("%lld | Philosopher %d is sleeping\n", cur_time, philo->id);
    if (action == THINK)
        printf("%lld | Philosopher %d is thinking\n", cur_time, philo->id);
    if (action == END)
        printf("%lld | Target reached, ending program\n", cur_time);
    if (action == DEAD)
        printf("%lld | Philosopher %d is dead\n", cur_time, philo->id);
    if (action == FORKS)
        printf("%lld | Philosopher %d picked two forks\n", cur_time, philo->id);
    pthread_mutex_unlock(data->print_lock);
}

void	philo_actions(t_philo *philo)
{
	t_data	*data;
	int		flag;

	flag = 0;
	data = philo->data;
	while (1)
	{
		if (flag == 1)
			return ;
        if (philo->next_to_eat == 1)
            eat(philo);//eat and sleep
		else if (philo->next_to_eat == 0)
			think(philo);//queue for fork
		if (data->death_flag == 1 || data->eat_max_flag == 1)
			flag = 1;

	}
}

void	think(t_philo *philo)
{
    philo->next_to_eat = 1;
    print_actions(philo, THINK);
	usleep(1000);//wait 1ms so the other threads have time to lock their forks
}

void	philo_sleep(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
    philo->data->sleepflag = 1;
    print_actions(philo, SLEEP);
	usleep(data->sleeptime * 1000);
    return ;
}
