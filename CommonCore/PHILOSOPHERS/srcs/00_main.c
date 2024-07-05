#include "../headers/philosophers.h"

void    philo_actions(t_philo *philo)
{
    //data->forks[philo->id] = fourchette correspondant au philo
    //data->philo_nb = last philo
    //philo with even IDs eat first
    //mutexes inside action functions or here ??
    //start by sending philos to eat, others think
    //philos done eating go sleep, philos thinking go eat
    //repeat
    t_data  *data;

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
        if (data->deathtimer)//if didnt eat until deathtimer
            data->death_flag = 1;
    }
    pthread_mutex_unlock(data->d_lock);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc < 5 || argc > 6)
		return (1);
	data = (t_data *)malloc(sizeof(t_data));
	struct_init(data, argv, argc);
	threads_init(data);
	free_data(data);
	return (0);
}
