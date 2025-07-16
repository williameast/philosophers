/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 10:49:58 by William           #+#    #+#             */
/*   Updated: 2025/07/16 11:08:40 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int ac, char **av)
{
	t_table	*table;
	t_phil	*philosophers;
	t_fork	*forks;

	if (ac < 5 || ac > 6)
	{
		printf("Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n", av[0]);
		return (1);
	}
	
	table = malloc(sizeof(t_table));
	if (!table)
		return (1);
	
	if (init_table(table, ac, av) != 0)
	{
		free(table);
		return (1);
	}
	
	// Create forks (same number as philosophers)
	forks = init_forks(table->num_philosophers);
	if (!forks)
	{
		free(table);
		return (1);
	}
	
	// Create philosophers
	philosophers = init_philosophers(table, forks, table->num_philosophers);
	if (!philosophers)
	{
		// Clean up forks
		for (int i = 0; i < table->num_philosophers; i++)
			kvp_destroy(&forks[i].available);
		free(forks);
		free(table);
		return (1);
	}
	
	// Set up table
	table->phil = philosophers;
	table->fork = forks;
	
	// Launch all philosophers
	if (launch_philosophers(table) != 0)
	{
		// Clean up on failure
		for (int i = 0; i < table->num_philosophers; i++)
		{
			kvp_destroy(&philosophers[i].last_meal_time);
			kvp_destroy(&philosophers[i].meals_consumed);
		}
		free(philosophers);
		for (int i = 0; i < table->num_philosophers; i++)
			kvp_destroy(&forks[i].available);
		free(forks);
		free(table);
		return (1);
	}
	
	launch_monitor(table);
	
	// Wait for all threads to complete
	pthread_join(table->mon_thread, NULL);
	for (int i = 0; i < table->num_philosophers; i++)
		pthread_join(philosophers[i].thread, NULL);
	
	cleanup(table);
	return (0);
}
