#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <sys/time.h>
# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_data
{
	pthread_t		*th;
	int				death_flag;
	int				philo_nb;
	int				fork_nb;
	int				deathtimer;
	int				eatingtime;
    int             sleepflag;
	int				sleeptime;
	int				eat_max;
    int             eat_max_flag;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*w_lock;
	pthread_mutex_t	*d_lock;
	pthread_mutex_t	*print_lock;
	struct s_philo	*philos;
}					t_data;

typedef struct s_philo
{
	int				id;
    int             next_to_eat;
	int				eat_counter;
	int				last_meal;
	t_data			*data;
}					t_philo;

int	ft_printf(const char *format, ...);
void	            struct_init(t_data *data, char **argv, int argc);
int	threads_init(t_data *data);
void	mutexes_init(t_data *data);
int	monitor_init(t_data *data);
void	mutexes_destroy(t_data *data);
void	threads_create(t_data *data, t_philo *philo);
void	threads_join(t_data *data);
void				philo_actions(t_philo *philo);
void	think(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	take_fork(t_philo *philo);
void	drop_fork(t_philo *philo);
void	eat(t_philo *philo);
void	monitor_routine(void *arg);
int	ft_atoi(const char *str);
void	free_data(t_data *data);
void	free_philo(t_philo *philo);
long long	gettime_ms(void);

#endif
