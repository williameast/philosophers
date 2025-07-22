/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:12:20 by weast             #+#    #+#             */
/*   Updated: 2025/07/22 10:38:05 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	eating(t_phil *phil)
{
	if (phil->id % 2 == 0)
	{
		pthread_mutex_lock(&phil->table->fork[phil->l_fork]);
		pthread_mutex_lock(&phil->table->fork[phil->r_fork]);
	}
	else
	{
		pthread_mutex_lock(&phil->table->fork[phil->r_fork]);
		pthread_mutex_lock(&phil->table->fork[phil->l_fork]);
	}
	print_action(phil, FORK_TAKEN);
	print_action(phil, FORK_TAKEN);
	print_action(phil, EATING);
	phil->meal_counter++;
	tick(phil, phil->table->config.time_to_eat);
	pthread_mutex_lock(&phil->table->eat_lock);
	phil->last_meal_time = get_time();
	pthread_mutex_unlock(&phil->table->eat_lock);
	pthread_mutex_unlock(&phil->table->fork[phil->r_fork]);
	pthread_mutex_unlock(&phil->table->fork[phil->l_fork]);
}

static int	single_philosopher(t_table *table)
{
	print_action(&table->phil[0], FORK_TAKEN);
	tick(&table->phil[0], table->config.time_to_die);
	set_completion_flag(&table->phil[0], 1);
	return (0);
}

void	*phil_routine(void *args)
{
	t_phil	*phil;

	phil = (t_phil *)args;
	if (phil->id % 2 == 0)
		usleep(phil->table->config.time_to_eat * 1000);
	while (sim_is_running(phil))
	{
		if (phil->table->config.philosophers == 1)
		{
			single_philosopher(phil->table);
			return (0);
		}
		eating(phil);
		print_action(phil, SLEEPING);
		tick(phil, phil->table->config.time_to_sleep);
		print_action(phil, THINKING);
	}
	return (0);
}

void	print_action(t_phil *phil, int status)
{
	pthread_mutex_lock(&phil->table->print_lock);
	if (status == DIED || status == FINISHED)
		print_special_status(phil, status);
	else if (sim_is_running(phil))
		print_normal_status(phil, status);
	pthread_mutex_unlock(&phil->table->print_lock);
}
