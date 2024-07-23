#include "../headers/philosophers.h"

static void    struct_init_helper(t_data *data)
{
    int i;

    i = 0;
    while (i < data->philo_nb)
	{
		data->th[i] = 0;
		i++;
	}
	data->print_lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	data->d_lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	data->w_lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->philo_nb);
	if (data->forks == NULL || data->print_lock == NULL || data->d_lock == NULL)
	{
		perror("Failed to allocate memory for mutexes");
		free(data->th);
		free(data->forks);
		free(data->print_lock);
		free(data->d_lock);
		free(data);
		return ;
	}
}

void	struct_init(t_data *data, char **argv, int argc)
{
	data->death_flag = 0;
	data->sleepflag = 0;
	data->eat_max_flag = 0;
    data->isprinted = 0;
	gettimeofday(&data->start, NULL);
	data->philo_nb = ft_atoi(argv[1]);
	data->fork_nb = ft_atoi(argv[1]);
	data->deathtimer = atoll(argv[2]);
	data->eatingtime = atoll(argv[3]);
	data->sleeptime = atoll(argv[4]);
	if (argc == 6)
		data->eat_max = ft_atoi(argv[5]);
	else
		data->eat_max = -1;
	data->th = (pthread_t *)malloc(sizeof(pthread_t) * data->philo_nb);
	if (data->th == NULL)
	{
		perror("Failed to allocate memory for thread IDs");
		free(data);
		return ;
	}
	struct_init_helper(data);
}

int	threads_init(t_data *data)
{
	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->philo_nb);
	if (data->philos == NULL)
	{
		perror("Failed to allocate memory for philosophers");
		return (1);
	}
	mutexes_init(data);
	if (monitor_init(data) != 0)
	{
		free_data(data);
		return (1);
	}
	threads_create(data, data->philos);
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
	pthread_mutex_init(data->w_lock, NULL);
	pthread_mutex_init(data->print_lock, NULL);
}

int	monitor_init(t_data *data)
{
	pthread_t	monitor;

	if (pthread_create(&monitor, NULL, (void *)monitor_routine,
			(void *)data) != 0)
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
	pthread_mutex_destroy(data->w_lock);
	pthread_mutex_destroy(data->print_lock);
}
