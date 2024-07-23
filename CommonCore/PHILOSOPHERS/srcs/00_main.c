#include "../headers/philosophers.h"

//add isdigit check
//add ft_atoll
long long ft_atoll(char *str)
{
    long long int   res;

    
}

int	main(int argc, char **argv)
{
	t_data	*data;
	if (argc < 5 || argc > 6)
	{
		printf("Usage: number_of_philosophers, time_to_die, \
time_to_eat, time_to_sleep, [number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
	{
		perror("Failed to allocate memory for data");
		return (1);
	}
	struct_init(data, argv, argc);
	if (threads_init(data) != 0)
	{
		free_data(data);
		return (1);
	}
	threads_join(data);
	mutexes_destroy(data);
	free_data(data);
	return (0);
}
