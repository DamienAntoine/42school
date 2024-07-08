#include "../headers/philosophers.h"

void    philo_actions(t_philo *philo)
{
    //data->forks[philo->id] = fourchette correspondant au philo
    //data->philo_nb = last philo
    //philo with even IDs eat first
    //mutexes inside action functions or here ??
    //start by sending philos to eat, others think
    //philos done eating go sleep, philos thinking go eat
    //repeat
    t_data  *data;

    data = philo->data;
    while (data->death_flag == 0)
    {
        if (philo->id % 2 == 0)
        {
            eat(philo);
        }
        else if (philo->id % 2 != 0)
        {
            think(philo);
        }
        if (data->deathtimer)//if didnt eat until deathtimer
            data->death_flag = 1;
    }
    pthread_mutex_unlock(data->d_lock);
}

void    take_fork(t_philo *philo)
{
    t_data  *data;

    data = philo->data;
    if (philo->id == data->philo_nb)//if last philo, take fork from first philo
    {
        pthread_mutex_lock(data->forks[philo->id]);
        pthread_mutex_lock(data->forks[0]);
    }
    else
    {
        pthread_mutex_lock(data->forks[philo->id]);
        pthread_mutex_lock(data->forks[(philo->id) + 1]);//locks philo's fork + neighbour's fork
    }
    ft_printf("%lf | Philosopher %d has taken a fork", gettimeofday(), philo->id);
}

void    take_fork(t_philo *philo)
{
    t_data  *data;

    data = philo->data;
    if (philo->id == data->philo_nb)//if last philo, take fork from first philo
    {
        pthread_mutex_unlock(data->forks[0]);
        pthread_mutex_unlock(data->forks[philo->id]);
    }
    else
    {
        pthread_mutex_unlock(data->forks[(philo->id) + 1]);
        pthread_mutex_unlock(data->forks[philo->id]);//locks philo's fork + neighbour's fork
    }
    ft_printf("%lf | Philosopher %d has taken a fork", gettimeofday(), philo->id);
}

void    eat(t_philo *philo)
{
    t_data  *data;

    data = philo->data;
    philo->eat_counter++;
    take_fork(philo);
    ft_printf("%lf | Philosopher %d is eating", gettimeofday(), philo->id);
    usleep(data->eatingtime);
    drop_fork(philo);
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