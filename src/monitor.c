/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 08:43:03 by William           #+#    #+#             */
/*   Updated: 2025/07/02 12:23:06 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void death_routine(t_table *sim, int id)
{
    DEBUG_PRINT("Philosopher %d died\n", id);
    print_status(sim, id, DIED);
    sim->stop_simulation = TRUE;
    pthread_mutex_unlock(&sim->meal_lock);
    exit(0); // Exit immediately when a philosopher dies
}

static int check_health(t_table *sim, int id)
{
    int fed_enough = TRUE;

    pthread_mutex_lock(&sim->meal_lock);
    if (get_relative_time(sim) - sim->philosophers[id].last_meal_time > sim->time_to_die)
    {
        DEBUG_PRINT("Philosopher %d failed health check (starved)\n", id);
        death_routine(sim, id);
        pthread_mutex_unlock(&sim->meal_lock);
        return FALSE;
    }
    if (sim->min_meals > 0 && sim->philosophers[id].meals_consumed < sim->min_meals)
        fed_enough = FALSE;
    pthread_mutex_unlock(&sim->meal_lock);
    return (fed_enough);
}

void *monitor_routine(void *arg)
{
    t_table *sim = (t_table *)arg;
    int id;
    int all_fed_enough;

    DEBUG_PRINT("Monitor routine started\n");
    while (!sim->stop_simulation)
    {
        DEBUG_PRINT("Monitor loop iteration\n");
        id = 0;
        all_fed_enough = TRUE;
        while (id < sim->num_philosophers && !sim->stop_simulation)
        {
            DEBUG_PRINT("Checking philosopher %d health\n", id);
            if (!check_health(sim, id))
                all_fed_enough = FALSE;
            id++;
            usleep(CPU_DELAY_TIME / sim->num_philosophers);
        }
        // Only check if all philosophers are fed enough when min_meals > 0
        if (sim->min_meals > 0 && all_fed_enough)
        {
            DEBUG_PRINT("All philosophers fed enough, stopping simulation\n");
            sim->stop_simulation = TRUE;
            exit(0); // Exit when all philosophers are fed enough
            break;
        }
    }
    DEBUG_PRINT("Monitor routine ended\n");
    return NULL;
}


void init_monitor(t_table *sim)
{
    pthread_t monitor;

    if (pthread_create(&monitor, NULL, monitor_routine, sim) != 0)
    {
        fprintf(stderr, "Failed to create monitor thread\n");
        DEBUG_PRINT("Failed to create monitor thread\n");
        sim->stop_simulation = TRUE;
    }
    else
        pthread_detach(monitor);
    DEBUG_PRINT("Monitor thread created and detached\n");
}
