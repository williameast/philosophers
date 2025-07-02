/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 12:40:36 by William           #+#    #+#             */
/*   Updated: 2025/07/02 11:54:46 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

void destroy_table(t_table *sim)
{
    int i;

    if (sim)
    {
        if (sim->forks)
        {
            for (i = 0; i < sim->num_philosophers; i++)
            {
                pthread_mutex_destroy(&sim->forks[i].mutex);
            }
            free(sim->forks);
        }
        if (sim->philosophers)
        {
            free(sim->philosophers);
        }
        pthread_mutex_destroy(&sim->meal_lock);
        pthread_mutex_destroy(&sim->print_lock);
        free(sim);
    }
}
