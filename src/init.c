/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 12:56:21 by William           #+#    #+#             */
/*   Updated: 2025/07/16 11:33:52 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	init_settings(int argc, char **argv, t_settings *settings)
{
	if (argc < 5 || argc > 6)
	{
		printf("Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n", argv[0]);
		return (-1);
	}
	settings->time_to_die = atoll(argv[2]);
	settings->time_to_eat = atoll(argv[3]);
	settings->time_to_sleep = atoll(argv[4]);
	if (argc == 6)
		settings->max_meals = atoi(argv[5]);
	else
		settings->max_meals = -1;
	if (settings->time_to_die < 0 || settings->time_to_eat < 0
		|| settings->time_to_sleep < 0 || settings->max_meals < -1)
	{
		printf("Invalid input values.\n");
		return (-1);
	}
	return (0);
}

t_fork	*init_forks(int num_forks)
{
	t_fork	*forks;
	int		i;

	forks = malloc(sizeof(t_fork) * num_forks);
	if (!forks)
		return (NULL);
	
	for (i = 0; i < num_forks; i++)
	{
		if (kvp_init(&forks[i].available, TRUE) != 0)
		{
			while (--i >= 0)
				kvp_destroy(&forks[i].available);
			free(forks);
			return (NULL);
		}
	}
	return (forks);
}

void	distribute_forks(t_phil *philosophers, t_fork *forks, int num_philosophers)
{
	int	i;

	for (i = 0; i < num_philosophers; i++)
	{
		philosophers[i].left_fork = &forks[i];
		philosophers[i].right_fork = &forks[(i + 1) % num_philosophers];
	}
}

t_phil	*init_philosophers(t_table *table, t_fork *forks, int num_philosophers)
{
	t_phil	*philosophers;
	int		i;

	philosophers = malloc(sizeof(t_phil) * num_philosophers);
	if (!philosophers)
		return (NULL);
	
	for (i = 0; i < num_philosophers; i++)
	{
		philosophers[i].id = i;
		philosophers[i].table = table;
		philosophers[i].state = THINKING;
		
		if (kvp_init(&philosophers[i].last_meal_time, table->init_time) != 0 ||
			kvp_init(&philosophers[i].meals_consumed, 0) != 0)
		{
			// Clean up already initialized philosophers
			while (--i >= 0)
			{
				kvp_destroy(&philosophers[i].last_meal_time);
				kvp_destroy(&philosophers[i].meals_consumed);
			}
			free(philosophers);
			return (NULL);
		}
	}
	
	// Distribute forks after all philosophers are initialized
	distribute_forks(philosophers, forks, num_philosophers);
	
	return (philosophers);
}

int	init_table(t_table *table, int ac, char **av)
{
	int	num_philosophers;

	if (init_settings(ac, av, &table->settings) < 0)
		return (1);
	
	num_philosophers = atoi(av[1]);
	if (num_philosophers <= 0 || num_philosophers > MAX_PHILOSOPHERS)
	{
		printf("Invalid number of philosophers. Must be between %d and %d.\n", 
			MIN_PHILOSOPHERS + 1, MAX_PHILOSOPHERS);
		return (1);
	}
	
	table->num_philosophers = num_philosophers;
	table->init_time = get_time();
	table->death_detected = 0;
	kvp_init(&table->print_lock, 0);
	return (0);
}
