#include "../headers/philosophers.h"

void	struct_init(t_data *data, char **argv, int argc)
{
    int i;

    i = 0;
    data->death_flag = 0;
    data->sleepflag = 0;
	data->philo_nb = ft_atoi(argv[1]);
	data->fork_nb = ft_atoi(argv[1]);
	data->deathtimer = ft_atoi(argv[2]);
	data->eatingtime = ft_atoi(argv[3]);
	data->sleeptime = ft_atoi(argv[4]);
	if (argc == 6)
		data->eat_max = ft_atoi(argv[5]);
	else
		data->eat_max = -1; // -1 if no limit
	data->th = (pthread_t *)malloc(sizeof(pthread_t) * data->philo_nb);
	if (data->th == NULL)
	{
		perror("Failed to allocate memory for thread IDs");
		free(data);
		return ;
	}
    while (i < data->philo_nb)
    {
        data->th[i] = 0;
        i++;
    }
    data->print_lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
    data->d_lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->philo_nb);
	if (data->forks == NULL)
	{
		perror("Failed to allocate memory for forks");
		free(data);
		return ;
	}
}

int	threads_init(t_data *data)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo) * data->philo_nb);
	if (philo == NULL)
	{
		perror("Failed to allocate memory for philosophers");
		return (1);
	}
    data->philos = philo;
	mutexes_init(data);
	threads_create(data, philo);
	return (0);
}

void	mutexes_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(data->d_lock, NULL);
	pthread_mutex_init(data->print_lock, NULL);
	//pthread_mutex_init(data->meal_lock, NULL);
}

int	monitor_init(t_data *data)
{
	pthread_t monitor;

	if (pthread_create(&monitor, NULL, (void *)monitor_routine, (void *)data) != 0)
	{
		perror("Failed to create monitor thread");
		return (1);
	}
	pthread_detach(monitor);
	return (0);
}

void	mutexes_destroy(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(data->d_lock);
	pthread_mutex_destroy(data->print_lock);
	//pthread_mutex_destroy(data->meal_lock);
}
