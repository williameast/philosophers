/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 11:59:09 by weast             #+#    #+#             */
/*   Updated: 2025/07/02 12:44:02 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


static void *philosopher_routine(void *arg)
{
    t_phil *phil = (t_phil *)arg;
    t_table *sim = (t_table *)phil->sim;


    DEBUG_PRINT("Philosopher %d routine started\n", phil->id);

    while (!sim->stop_simulation)
    {
        // Think
        print_status(sim, phil->id, THINKING);

        // Take forks
        take_forks(sim, phil->id);

        // Eat
        pthread_mutex_lock(&sim->meal_lock);
        phil->last_meal_time = get_time();
        phil->meals_consumed++;
        pthread_mutex_unlock(&sim->meal_lock);
        print_status(sim, phil->id, EATING);
        usleep(sim->time_to_eat * 1000);

        // Put down forks
        put_forks(sim, phil->id);

        // Sleep
        print_status(sim, phil->id, SLEEPING);
        usleep(sim->time_to_sleep * 1000);
    }
    DEBUG_PRINT("Philosopher %d routine ended\n", phil->id);
    return NULL;
}

void create_philosophers(t_table *sim)
{
    int i;

    i = 0;
    while (i < sim->num_philosophers)
    {
        sim->philosophers[i].sim = sim;
        if (pthread_create(&sim->philosophers[i].thread, NULL, philosopher_routine, &sim->philosophers[i]) != 0)
        {
            fprintf(stderr, "Failed to create philosopher thread\n");
            sim->stop_simulation = TRUE;
            break;
        }
        i++;
    }
}

void join_philosophers(t_table *sim)
{
    int i;

    i = 0;
    while (i < sim->num_philosophers)
    {
        pthread_join(sim->philosophers[i].thread, NULL);
        i++;
    }
}
