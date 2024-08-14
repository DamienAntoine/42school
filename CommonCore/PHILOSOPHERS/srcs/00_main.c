/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:34:19 by dantoine          #+#    #+#             */
/*   Updated: 2024/08/06 12:34:21 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosophers.h"

// add isdigit check
// add ft_atoll

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc < 5 || argc > 6 || !checkinputs(argv))
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
