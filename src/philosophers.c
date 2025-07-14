/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 11:59:09 by weast             #+#    #+#             */
/*   Updated: 2025/07/14 16:50:01 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"


static void	eating(t_table *table, t_phil *phil)
{
	long long meals;

	meals = kvp_get(phil->meals_consumed);

	fork_set_busy(phil->left);
	log_state(table, phil->id, FORK_TAKEN);
	fork_set_busy(phil->right);
	log_state(table, phil->id, FORK_TAKEN);
	// Eating
	log_state(table, phil->id, EATING);
	kvp_set(phil->last_meal_time, get_time());
	usleep(table->settings.time_to_eat * 1000);
	kvp_set(phil->meals_consumed, meals + 1);
	// Release forks
	fork_set_available(phil->left);
	fork_set_available(phil->right);
}

static void	sleeping(t_table *table, t_phil *phil)
{
	log_state(table, phil->id, SLEEPING);
	usleep(table->settings.time_to_sleep * 1000);
}

static void	thinking(t_table *table, t_phil *phil)
{
	log_state(table, phil->id, THINKING);
}

void *philosopher_routine(void *arg)
   {
	t_phil *phil = (t_phil *)arg;
	t_table *table = phil->table;

    printf("Philosopher %d starting\n", phil->id);

	while (!kvp_get(table->sim_ended))
	{
		if (kvp_get(table->sim_ended)) break;
		eating(table, phil);
		if (kvp_get(table->sim_ended)) break;
		sleeping(table, phil);
		if (kvp_get(table->sim_ended)) break;
		thinking(table, phil);
	}
	printf("Philosopher %d exiting\n", phil->id);
	return NULL;
   }
