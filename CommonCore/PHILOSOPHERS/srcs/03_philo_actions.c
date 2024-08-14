/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_philo_actions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:34:34 by dantoine          #+#    #+#             */
/*   Updated: 2024/08/06 12:34:35 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosophers.h"

void	print_actions(t_philo *philo, int action)
{
	t_data			*data;
	long long int	cur_time;

	data = philo->data;
	cur_time = gettime_ms(data);
	pthread_mutex_lock(data->print_lock);
	if (action == EAT)
		printf("%lld Philosopher %d is eating\n", cur_time, philo->id);
	if (action == SLEEP)
		printf("%lld Philosopher %d is sleeping\n", cur_time, philo->id);
	if (action == THINK)
		printf("%lld Philosopher %d is thinking\n", cur_time, philo->id);
	if (action == DEAD)
		printf("%lld Philosopher %d is dead\n", cur_time, philo->id);
	if (action == FORKS)
		printf("%lld Philosopher %d picked two forks\n", cur_time, philo->id);
	pthread_mutex_unlock(data->print_lock);
}

void	philo_actions(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	while (1)
	{
		pthread_mutex_lock(data->w_lock);
		if (data->death_flag || data->eat_max_flag)
		{
			pthread_mutex_unlock(data->w_lock);
			break ;
		}
		pthread_mutex_unlock(data->w_lock);
		if (philo->next_to_eat == 1)
			eat(philo);
		else if (philo->next_to_eat == 0)
			think(philo);
		pthread_mutex_lock(data->w_lock);
		if (data->death_flag || data->eat_max_flag)
		{
			pthread_mutex_unlock(data->w_lock);
			break ;
		}
		pthread_mutex_unlock(data->w_lock);
	}
}

void	think(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(data->w_lock);
	if (data->death_flag || data->eat_max_flag)
	{
		if (philo->is_holding_forks == 1)
			drop_fork(philo);
		pthread_mutex_unlock(data->w_lock);
		return ;
	}
	pthread_mutex_unlock(data->w_lock);
	philo->next_to_eat = 1;
	if (data->death_flag || data->eat_max_flag)
	{
		pthread_mutex_unlock(data->w_lock);
		return ;
	}
	print_actions(philo, THINK);
	usleep(100);
}

void	philo_sleep(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(data->w_lock);
	if (data->death_flag || data->eat_max_flag)
	{
		if (philo->is_holding_forks == 1)
			drop_fork(philo);
		pthread_mutex_unlock(data->w_lock);
		return ;
	}
	pthread_mutex_unlock(data->w_lock);
	philo->data->sleepflag = 1;
	if (data->death_flag || data->eat_max_flag)
	{
		if (philo->is_holding_forks == 1)
			drop_fork(philo);
		pthread_mutex_unlock(data->w_lock);
		return ;
	}
	print_actions(philo, SLEEP);
	better_usleep(data->sleeptime, data);
}
