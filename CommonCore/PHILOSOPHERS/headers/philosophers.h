#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>

typedef struct s_data
{
	pthread_t		*th;
	int				death_flag;
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
	struct s_philo	*philos;
}					t_data;

typedef struct s_philo
{
	int				id;
	int				eat_counter;
	int				last_meal;
	t_data			*data;
}					t_philo;

void				philo_actions(t_philo *philo);

#endif
