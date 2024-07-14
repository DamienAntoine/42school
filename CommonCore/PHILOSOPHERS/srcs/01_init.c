#include "../headers/philosophers.h"

void	struct_init(t_data *data, char **argv, int argc)
{
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
		return (1);
	}
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->philo_nb);
	if (data->forks == NULL)
	{
		perror("Failed to allocate memory for forks");
		free(data);
		return (1);
	}
}

int	threads_init(t_data *data)
{
	t_philo	*philo;
	int		i;
	int		flag;

	philo = (t_philo *)malloc(sizeof(t_philo) * data->philo_nb);
	if (philo == NULL)
	{
		perror("Failed to allocate memory for philosophers");
		return (1);
	}
	mutexes_init(data);
	threads_create(data, philo);
	data->philos = philo;
	return (0);
}

int	monitor_init(t_data *data, t_philo *philo)
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

void	mutexes_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->d_lock, NULL);
	pthread_mutex_init(&data->w_lock, NULL);
	pthread_mutex_init(&data->meal_lock, NULL);
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
	pthread_mutex_destroy(&data->d_lock);
	pthread_mutex_destroy(&data->w_lock);
	pthread_mutex_destroy(&data->meal_lock);
}
