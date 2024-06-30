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
}

void	threads_init(t_data *data, pthread_t *th)
{
	int	i;
	i = 0;
	while (i < data->philo_nb)
	{
		if (pthread_create(th + 1, NULL, function, NULL) != 0)
		{
			perror("Failed to create thread");
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < data->philo_nb)
	{
		if (pthread_join(th[i], NULL) != 0)
			return (2);
	}
}

int	main(int argc, char **argv)
{
	pthread_t *th;
	t_data	*data;

	if (argc < 5 || argc > 6)
		return (1);
	struct_init(data, argv, argc);
	threads_init(data, th);
	return (0);
}
