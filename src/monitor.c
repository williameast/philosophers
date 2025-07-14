/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 08:43:03 by William           #+#    #+#             */
/*   Updated: 2025/07/11 16:32:35 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*monitor_routine(void *arg)
{
	t_table	*table = (t_table *)arg;
	int		i;
	long long	now;

	while (!kvp_get(&table->sim_ended))
	{
		i = 0;
		now = get_time();
		while (i < table->phil_count)
		{
			long long last_meal = kvp_get(&table->phils[i].last_meal_time);
			if (now - last_meal > table->settings.time_to_die)
			{
				log_state(table, table->phils[i].id, "died");
				kvp_set(&table->sim_ended, 1);
				return (NULL);
			}
			i++;
		}
		usleep(1000); // Check every ms
	}
	return (NULL);
}
