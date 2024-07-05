#include "../headers/philosophers.h"

void    take_fork(t_philo *philo)
{
    t_data  *data;

    data = philo->data;
    pthread_mutex_lock(data->forks);
    
    pthread_mutex_lock(data->forks);//find a way to take the fork from the next philo
    ft_printf("%lf | Philosopher %d has taken a fork", gettimeofday(), philo->id);
}

void    eat(t_philo *philo)
{
    t_data  *data;

    data = philo->data;
    philo->eat_counter++;
    usleep(data->eatingtime);
    ft_printf("%lf | Philosopher %d is eating", gettimeofday(), philo->id);
    if (philo->eat_counter == data->eat_max)
    {
        //stop simulation
    }
    //find a way to print time in ms
}

void    think(t_philo *philo)
{
    t_data  *data;

    data = philo->data;
    usleep(data->eatingtime);
    ft_printf("%lf | Philosopher %d is thinking", gettimeofday(), philo->id);
}

void    sleep(t_philo *philo)
{
    t_data  *data;

    data = philo->data;
    usleep(data->sleeptime);
    ft_printf("%lf | Philosopher %d is sleeping", gettimeofday(), philo->id);
}

void    death(t_philo *philo)
{
    t_data  *data;

    data = philo->data;
    ft_printf("%lf | Philosopher %d died", gettimeofday(), philo->id);
    exit(0);
    //free everything and quit when someone dies
}