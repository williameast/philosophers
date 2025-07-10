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
        DEBUG_PRINT("Philosopher %d is thinking\n", phil->id);
        print_status(sim, phil->id, THINKING);

        // Take forks
        DEBUG_PRINT("Philosopher %d is trying to take forks\n", phil->id);
        take_forks(sim, phil->id);
        DEBUG_PRINT("Philosopher %d has taken forks\n", phil->id);

        // Eat
        pthread_mutex_lock(&sim->meal_lock);
        phil->last_meal_time = get_relative_time(sim);
        phil->meals_consumed++;
        pthread_mutex_unlock(&sim->meal_lock);
        DEBUG_PRINT("Philosopher %d is eating\n", phil->id);
        print_status(sim, phil->id, EATING);
        // Sleep in smaller chunks to check stop_simulation
        for (int i = 0; i < sim->time_to_eat && !sim->stop_simulation; i++) {
            usleep(1000); // 1ms chunks
        }

        // Put down forks
        DEBUG_PRINT("Philosopher %d is putting down forks\n", phil->id);
        put_forks(sim, phil->id);

        // Sleep
        DEBUG_PRINT("Philosopher %d is sleeping\n", phil->id);
        print_status(sim, phil->id, SLEEPING);
        // Sleep in smaller chunks to check stop_simulation
        for (int i = 0; i < sim->time_to_sleep && !sim->stop_simulation; i++) {
            usleep(1000); // 1ms chunks
        }
        
        // Check if simulation should stop after each cycle
        if (sim->stop_simulation)
            break;
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
            DEBUG_PRINT("Failed to create philosopher thread %d\n", i);
            sim->stop_simulation = TRUE;
            break;
        }
        DEBUG_PRINT("Philosopher thread %d created\n", i);
        i++;
    }
}

void join_philosophers(t_table *sim)
{
    int i;

    i = 0;
    while (i < sim->num_philosophers)
    {
        DEBUG_PRINT("Joining philosopher thread %d\n", i);
        pthread_join(sim->philosophers[i].thread, NULL);
        DEBUG_PRINT("Philosopher thread %d joined\n", i);
        i++;
    }
}
