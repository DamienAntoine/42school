/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:34:12 by dantoine          #+#    #+#             */
/*   Updated: 2024/08/06 13:14:35 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define EAT 1
# define SLEEP 2
# define THINK 3
# define END 4
# define DEAD 5
# define FORKS 6

typedef struct timer
{
	struct timeval	start;
}					t_timer;

typedef struct s_data
{
	pthread_t		*th;
	int				death_flag;
	int				philo_nb;
	int				fork_nb;
	long long int	deathtimer;
	long long int	eatingtime;
	int				sleepflag;
	long long int	sleeptime;
	int				eat_max;
	int				eat_max_nb;
	int				eat_max_flag;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*w_lock;
	pthread_mutex_t	*d_lock;
	pthread_mutex_t	*print_lock;
	struct timeval	start;
	struct s_philo	*philos;
}					t_data;

typedef struct s_philo
{
	int				id;
	int				next_to_eat;
	int				eat_counter;
	int				is_holding_forks;
	long long int	last_meal;
	t_data			*data;
}					t_philo;

void				struct_init(t_data *data, char **argv, int argc);
int					threads_init(t_data *data);
void				mutexes_init(t_data *data);
int					monitor_init(t_data *data);
void				mutexes_destroy(t_data *data);
void				threads_create(t_data *data, t_philo *philo);
void				threads_join(t_data *data);
void				print_actions(t_philo *philo, int action);
void				philo_actions(t_philo *philo);
void				think(t_philo *philo);
void				philo_sleep(t_philo *philo);
void				take_fork(t_philo *philo);
void				drop_fork(t_philo *philo);
void				eat(t_philo *philo);
void				eat_helper(t_philo *philo, t_data *data);
void				monitor_routine(void *arg);
int					ft_atoi(const char *str);
void				free_data(t_data *data);
void				free_philo(t_philo *philo);
int					is_end(t_philo *philo);
int					checkinputs(char **argv);
int					ft_isdigit(int c);
long long			ft_atoll(const char *str);
void				start_timer(t_data *timer);
long long			gettime_ms(t_data *timer);
void				better_usleep(long long time, t_data *data);

#endif
