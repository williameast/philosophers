/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 13:25:31 by William           #+#    #+#             */
/*   Updated: 2025/07/16 10:37:58 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	launch_philosophers(t_table *table)
{
	int	i;

	for (i = 0; i < table->num_philosophers; i++)
	{
		printf("Creating philosopher %d\n", i);
		if (launch_philosopher(&table->phil[i]) != 0)
		{
			// If one philosopher fails to launch, we should handle this
			fprintf(stderr, "Failed to create philosopher %d\n", i);
			return (1);
		}
	}
	return (0);
}

void	*monitor_simulation(void *arg)
{
	t_table		*table;
	int			i;
	long long	current_time;
	long long	last_meal;

	table = (t_table *)arg;
	while (1)
	{
		for (i = 0; i < table->num_philosophers; i++)
		{
			current_time = get_time();
			last_meal = kvp_get(&table->phil[i].last_meal_time);
			if (current_time - last_meal > table->settings.time_to_die)
			{
				dying(&table->phil[i]);
				return (NULL); // Exit the monitor thread
			}
		}
		usleep(500);
	}
	return (NULL);
}

int	launch_philosopher(t_phil *phil)
{
	puts("creating philo");
	if (pthread_create(&phil->thread, NULL, phil_lifecycle, (void *)phil))
	{
		fprintf(stderr, "Failed to create philosopher thread\n");
		return (1);
	}
	return (0);
}

int	launch_monitor(t_table *table)
{
	puts("creating monitor");
	if (pthread_create(&table->mon_thread, NULL, monitor_simulation,
			(void *)table))
	{
		fprintf(stderr, "Failed to create monitor thread\n");
		return (1);
	}
	return (0);
}
