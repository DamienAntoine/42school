#include "../headers/philosophers.h"

void    take_fork(t_philo *philo)
{
    t_data  *data;

    data = philo->data;
    if (philo->id == data->philo_nb)//if last philo, take fork from first philo
    {
        pthread_mutex_lock(&data->forks[philo->id]);
        pthread_mutex_lock(&data->forks[0]);
    }
    else
    {
        pthread_mutex_lock(&data->forks[philo->id]);
        pthread_mutex_lock(&data->forks[(philo->id) + 1]);//locks philo's fork + neighbour's fork
    }
    ft_printf("%lf | Philosopher %d has taken a fork", gettimeofday(), philo->id);
}

void    drop_fork(t_philo *philo)
{
    t_data  *data;

    data = philo->data;
    if (philo->id == data->philo_nb)//if last philo, drop fork from first philo
    {
        pthread_mutex_unlock(&data->forks[0]);
        pthread_mutex_unlock(&data->forks[philo->id]);
    }
    else
    {
        pthread_mutex_unlock(&data->forks[(philo->id) + 1]);
        pthread_mutex_unlock(&data->forks[philo->id]);//unlocks philo's fork + neighbour's fork
    }
    ft_printf("%lf | Philosopher %d has taken a fork", gettimeofday(), philo->id);
}

void    eat(t_philo *philo)
{
    t_data  *data;

    data = philo->data;
    philo->eat_counter++;
    
    take_fork(philo); //lock 2 forks for current philo
    ft_printf("%lf | Philosopher %d is eating", gettimeofday(), philo->id);
    usleep(data->eatingtime);
    drop_fork(philo); //drops the 2 forks
    philo_sleep(philo);
    if (philo->eat_counter == data->eat_max)
    {
        ft_printf("%ls | Target reached, program closing.", gettimeofday());
        free_data(data);
        exit(0);
    }
    //find a way to print time in ms
}