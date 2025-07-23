/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:14:21 by weast             #+#    #+#             */
/*   Updated: 2025/07/23 16:02:01 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdlib.h>

static int	check_death(t_phil *phil)
{
	long long	current_time;
	long long	time_since_last_meal;

	current_time = get_time();
	time_since_last_meal = current_time - phil->last_meal_time;
	if (time_since_last_meal >= phil->table->config.time_to_die)
	{
		set_completion_flag(phil, 1);
		print_action(phil, DIED);
		return (1);
	}
	return (0);
}

static int	check_meals(t_phil *phil)
{
	pthread_mutex_lock(&phil->table->meal_count_lock);
	if (phil->table->meals_needed >= phil->table->config.philosophers)
	{
		set_completion_flag(phil, 1);
		print_action(phil, FINISHED);
		pthread_mutex_unlock(&phil->table->meal_count_lock);
		return (1);
	}
	if (phil->table->config.max_meals > 0
		&& phil->meal_counter >= phil->table->config.max_meals
		&& !phil->done_eating)
	{
		phil->done_eating = 1;
		phil->table->meals_needed++;
		if (phil->table->meals_needed >= phil->table->config.philosophers)
		{
			set_completion_flag(phil, 1);
			print_action(phil, FINISHED);
			pthread_mutex_unlock(&phil->table->meal_count_lock);
			return (1);
		}
	}
	pthread_mutex_unlock(&phil->table->meal_count_lock);
	return (0);
}

static int	monitor_thread(t_phil *phil)
{
	pthread_mutex_lock(&phil->table->eat_lock);
	if (check_death(phil) || check_meals(phil))
	{
		pthread_mutex_unlock(&phil->table->eat_lock);
		return (1);
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
		i = 0;
		while (i < table->config.philosophers)
		{
			if (monitor_thread(&table->phil[i]))
			{
				continue_flag = 0;
				break ;
			}
			i++;
		}
		if (continue_flag)
			usleep(100);
	}
	rejoin_threads(table);
}
