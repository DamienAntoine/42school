#include "../headers/philosophers.h"

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
