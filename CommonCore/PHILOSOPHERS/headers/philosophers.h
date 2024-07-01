#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h>

typedef struct s_data
{
	pthread_t		*th;
	int				philo_nb;
	int				fork_nb;
	int				deathtimer;
	int				eatingtime;
	int				sleeptime;
	int				eat_max;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*w_lock;
	pthread_mutex_t	*d_lock;
	pthread_mutex_t	*meal_lock;
}		t_data;

typedef struct s_philo
{
	int	id;
	t_data *data;
}		t_philo;

#endif
