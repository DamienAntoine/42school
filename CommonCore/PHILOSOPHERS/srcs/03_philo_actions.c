#include "../headers/philosophers.h"

//eat, sleep, if not eating and not sleeping, think
//deathtimer starts at the start of program and resets when philo starts eating
//if philo doesnt it until deathtimer is reached, end
    //find a way to create a countdown for deathtimer

void    philo_actions(t_philo *philo)
{
    //&data->forks[philo->id] = fourchette correspondant au philo
    //data->philo_nb = last philo
    //philo with even IDs eat first
    //start by sending philos to eat, others think
    //philos done eating go sleep, philos thinking go eat
    //repeat
        //find a way to tell the program a philosopher is done eating so the others can start
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
        if (data->death_flag == 1)
        {
            data->death_flag = 0;
            death(philo);
            exit(0); //need pthread join before exit ??
        }
    }
}

void    think(t_philo *philo)
{
    t_data  *data;

    data = philo->data;
    ft_printf("%lf | Philosopher %d is thinking", gettimeofday(), philo->id);//print Thinking when philosopher is queuing for a fork ?
    usleep(data->eatingtime);//Find a way for the philosophers to know when forks are available
}

void    philo_sleep(t_philo *philo)
{
    t_data  *data;

    data = philo->data;
    ft_printf("%lf | Philosopher %d is sleeping", gettimeofday(), philo->id);
    usleep(data->sleeptime);
}

void    death(t_philo *philo)
{
    t_data  *data;

    data = philo->data;
    ft_printf("%lf | Philosopher %d died", gettimeofday(), philo->id);
    free_data(data);
    free_philo(philo); //need pthread join before exit ??
    //free everything and quit when someone dies
}