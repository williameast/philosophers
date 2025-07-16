/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 08:43:03 by William           #+#    #+#             */
/*   Updated: 2025/07/15 14:49:40 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int init_monitor(t_table *table)
{
    printf("trying to create Monitor thread...\n");

    if (pthread_create(&table->monitor_thread, NULL, monitor_routine, table) != 0)
    {
        fprintf(stderr, "Failed to create monitor thread\n");
        return (1);
	}
	return 0;
    pthread_cre
}

void *monitor_routine(void *arg)
{
    t_table *table = (t_table *)arg;
    int i;
    long long now;
    int all_ate_enough = 1;
    usleep(1000);
    while (!kvp_get(table->sim_ended))
    {
        i = 0;
        now = get_time();
        all_ate_enough = 1;
        while (i < table->phil_count)
        {
            long long last_meal = kvp_get(table->phils[i].last_meal_time);
            long long meals_eaten = kvp_get(table->phils[i].meals_consumed);

            if (now - last_meal > table->settings.time_to_die)
            {
                log_state(table, table->phils[i].id, "died");
                kvp_set(table->sim_ended, 1);
                printf("Philosopher %d died. Ending simulation.\n", i+1);
                return NULL;
            }
            if (table->settings.max_meals > 0 && meals_eaten < table->settings.max_meals)
            {
                all_ate_enough = 0;
            }
            i++;
        }
        if (table->settings.max_meals > 0 && all_ate_enough)
        {
            printf("All philosophers have eaten enough. Simulation ending.\n");
            kvp_set(table->sim_ended, 1);
            return NULL;
        }
        printf("Monitor sleeping for 1ms...\n");
        usleep(1000); // Check every ms
    }
    return NULL;
}
