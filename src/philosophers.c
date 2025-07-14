/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 11:59:09 by weast             #+#    #+#             */
/*   Updated: 2025/07/11 15:33:59 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/* // replace printf with a status printer with its own lock. */
/* static void	eating(t_phil *phil) */
/* { */
/*         fork_set_busy(phil->left); */
/*         fork_set_busy(phil->right); */
/*         fork_set_available(phil->left); */
/*         fork_set_available(phil->right); */
/*         usleep(1000); */
/* } */
/* void	*philosopher_routine(void *arg) */
/* { */
/*     t_phil *phil = (t_phil *)arg; */

/*     while (TRUE) */
/*     { */
/*         while (!fork_is_available(phil->left) || !fork_is_available(phil->right)) */
/*             usleep(100); */

/*         eating(phil); */
/*         sleeping(phil); */
/*         thinking(phil); */
/*     } */
/*     return NULL; */
/* } */

static void	eating(t_table *table, t_phil *phil)
{
		fork_set_busy(phil->left);  // e.g. lock and set available=0
		log_state(table, phil->id, FORK_TAKEN);
		fork_set_busy(phil->right);  // e.g. lock and set available=0
		log_state(table, phil->id, FORK_TAKEN);

		// Eating
		log_state(table, phil->id, EATING);
		phil->last_meal_time = get_time();
		usleep(table->settings.time_to_eat * 1000);
		phil->meals_consumed++;

		// Release forks
		fork_set_available(phil->left);
		fork_set_available(phil->right);
}

static void	sleeping(t_table *table, t_phil *phil)
{
		// Sleeping
		log_state(table, phil->id, SLEEPING);
		usleep(table->settings.time_to_sleep * 1000);
}

static void	thinking(t_table *table, t_phil *phil)
{
		// Thinking
		log_state(table, phil->id, THINKING);
}

void	*philosopher_routine(void *arg)
{
	t_phil	*phil = (t_phil *)arg;
	t_table	*table = phil->table; // Add this pointer to t_phil if not present!

	while (!kvp_get(&table->sim_ended))
	{
        eating(table, phil);
        sleeping(table, phil);
        thinking(table, phil);
	}
	return (NULL);
}
