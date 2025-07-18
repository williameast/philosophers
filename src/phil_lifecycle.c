/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_lifecycle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 13:23:38 by William           #+#    #+#             */
/*   Updated: 2025/07/16 11:44:12 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"


void	action(t_phil *phil , int delay)
{
	log_action(&phil->table->print_lock, phil);
	// 1ms
	usleep(delay * 1000);
}

static void	eating(t_phil *phil)
{
	// Try to take both forks
	while (!take_both_forks(phil))
	{
		// If we can't get both forks, wait a bit and try again
		usleep(1000); // Wait 1ms before trying again
		if (phil->table->death_detected)
			return;
	}
	kvp_set(&phil->last_meal_time, get_time());
	phil->state = EATING;
	action(phil, phil->table->settings.time_to_eat);
	release_both_forks(phil);
}

static void	sleeping(t_phil *phil)
{
	phil->state = SLEEPING;
	action(phil, phil->table->settings.time_to_sleep);
}

static void	thinking(t_phil *phil)
{
	phil->state = THINKING;
	action(phil, 200);
}

void	dying(t_phil *phil)
{
	phil->state = DYING;
	phil->table->death_detected = 1;
	action(phil, 0);
}


void	*phil_lifecycle(void *arg)
{
	t_phil	*phil;
	int		i;

	phil = (t_phil *)arg;
	int max_meals = phil->table->settings.max_meals;
	i = 0;
	while ((max_meals == -1 || i < max_meals) && !phil->table->death_detected)
	{
		eating(phil);
		if (phil->table->death_detected)
			break;

		sleeping(phil);
		if (phil->table->death_detected)
			break;

		thinking(phil);
		if (phil->table->death_detected)
			break;

		if (max_meals != -1)
			i++; // Only increment if max_meals is not infinite
	}
	return (NULL);
}
