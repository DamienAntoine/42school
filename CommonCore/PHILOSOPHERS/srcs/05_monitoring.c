/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_monitoring.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:34:43 by dantoine          #+#    #+#             */
/*   Updated: 2024/08/06 12:34:43 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosophers.h"

void	monitor_routine(void *arg)
{
	t_data		*data;
	int			i;
	long long	current_time;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		current_time = gettime_ms(data);
		while (i < data->philo_nb)
		{
			if ((current_time - data->philos[i].last_meal) > data->deathtimer)
			{
				pthread_mutex_lock(data->w_lock);
				data->death_flag = 1;
				pthread_mutex_unlock(data->w_lock);
				print_actions(&data->philos[i], DEAD);
				return ;
			}
			if (data->eat_max_flag)
				return ;
			i++;
		}
		usleep(1000);
	}
}
