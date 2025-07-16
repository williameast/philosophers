/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:14:21 by weast             #+#    #+#             */
/*   Updated: 2025/07/16 16:37:40 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>


void	free_table(t_table *table)
{
	free(table->phil);
	free(table->fork);
}

void	destroy_locks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->config.philosophers)
	{
		pthread_mutex_destroy(&table->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&table->print_lock);
	pthread_mutex_destroy(&table->eat_lock);
	pthread_mutex_destroy(&table->finish_lock);
	free_table(table);
}

void	rejoin_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->config.philosophers)
	{
		pthread_join(table->phil[i].thread, NULL);
		i++;
	}
	destroy_locks(table);
}

int	monitor_thread(t_phil *phil)
{
	pthread_mutex_lock(&phil->table->eat_lock);
	if (get_time() - phil->last_meal_time >= phil->table->config.time_to_die)
	{
		print_action(phil, DIED);
		set_completion_flag(phil, 1);
		pthread_mutex_unlock(&phil->table->eat_lock);
		return (1);
	}
	else if (phil->table->config.max_meals > 0
		&& phil->meal_counter >= phil->table->config.max_meals)
	{
		phil->table->meals_needed++;
		if (phil->table->meals_needed >= phil->table->config.philosophers)
		{
			set_completion_flag(phil, 1);
			print_action(phil, FINISHED);
			pthread_mutex_unlock(&phil->table->eat_lock);
			return (1);
		}
	}
	pthread_mutex_unlock(&phil->table->eat_lock);
	return (0);
}

void	init_monitor(t_table *table)
{
	int	i;
	int	continue_flag;

	continue_flag = 1;
	while (continue_flag)
	{
		i = -1;
		/* table->ate_enough = 0; */
		while (i < table->config.philosophers)
		{
			if (continue_flag && monitor_thread(&table->phil[i]))
				continue_flag = 0;
			i++;
		}
		usleep(10);
	}
	rejoin_threads(table);
}
