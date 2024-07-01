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
		data->eat_max = -1;
	data->th = (pthread_t *)malloc(sizeof(pthread_t) * data->philo_nb);
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->philo_nb);
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

int	threads_init(t_data *data)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)malloc(sizeof(t_philo) * data->philo_nb);
	if (philo == NULL)
	{
		perror("Failed to allocate memory for philosophers");
		return (1);
	}
	data->th = (pthread_t *)malloc(sizeof(pthread_t) * data->philo_nb);
	if (data->th == NULL)
	{
		perror("Failed to allocate memory for thread IDs");
		free(philo);
		return (1);
	}
	mutexes_init(data);
	threads_create(data, philo);
	threads_join(data);
	free(philo);
	free(data->th);
	mutexes_destroy(data);
	return (0);
}

void	threads_create(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		philo[i].id = i;
		philo[i].data = data;
		if (pthread_create(&data->th[i], NULL, function,
				(void *)&philo[i]) != 0)
		{
			perror("Failed to create thread");
			free(philo);
			exit(1);
		}
		i++;
	}
}

void	threads_join(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		if (pthread_join(data->th[i], NULL) != 0)
			exit(2);
		i++;
	}
}

void	free_data(t_data *data)
{
	free(data->th);
	free(data->forks);
	free(data->w_lock);
	free(data->d_lock);
	free(data->meal_lock);
	free(data);
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
