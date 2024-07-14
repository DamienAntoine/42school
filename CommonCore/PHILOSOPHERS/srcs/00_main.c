#include "../headers/philosophers.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc < 5 || argc > 6)
		return (1);
	data = (t_data *)malloc(sizeof(t_data));
	struct_init(data, argv, argc);
	if (threads_init(data) != 0)
	{
		free_data(data);
		return (1);
	}
	if (monitor_init(data) != 0)
	{
		free_data(data);
		return (1);
	}
	threads_join(data);
	mutexes_destroy(data);
	free_data(data);
	return (0);
}
