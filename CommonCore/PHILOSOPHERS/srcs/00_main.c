#include "../headers/philosophers.h"

//to do:
//  -check if all threads come back to threads_join function in every possible end
//  -makefile
//  -norm
//  -add &lld support to ft_printf
//  -replace every printf with ft_printf
//  -add mutexes on every function that prints so they dont print at the same time
//  -change makefile so libftprintf.a gets cleaned too
int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc < 5 || argc > 6) //add isdigit check
    {
        ft_printf("Usage: number_of_philosophers, time_to_die, \
        time_to_eat, time_to_sleep, [number_of_times_each_philosopher_must_eat]\n");
		return (1);
    }
	data = (t_data *)malloc(sizeof(t_data));
	struct_init(data, argv, argc);
	if (monitor_init(data) != 0)
	{
		free_data(data);
		return (1);
	}
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
