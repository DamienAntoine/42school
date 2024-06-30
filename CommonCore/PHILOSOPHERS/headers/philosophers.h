#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h>

typedef struct s_data
{
	int	philo_nb;
	int	fork_nb;
	int	deathtimer;
	int	eatingtime;
	int	sleeptime;
	int	eat_max;
}		t_data;

#endif
