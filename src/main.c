/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:08:04 by weast             #+#    #+#             */
/*   Updated: 2025/07/17 12:08:05 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <pthread.h>
#include <stdlib.h>

int	instantiate_philosophers(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->config.philosophers)
	{
		if (pthread_create(&table->phil[i].thread, NULL, phil_routine,
				&table->phil[i]))
		{
			printf("[ERROR] Could not create threads.\n");
			rejoin_threads(table);
		}
		i++;
	}
	return (0);
}

int	init_locks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->config.philosophers)
	{
		if (pthread_mutex_init(&table->fork[i], NULL))
		{
			destroy_locks(table);
			printf("[ERROR] mutex initialization failiure\n");
			return (-1);
		}
		i++;
	}
	if (pthread_mutex_init(&table->print_lock, NULL)
		|| pthread_mutex_init(&table->eat_lock, NULL)
		|| pthread_mutex_init(&table->finish_lock, NULL))
	{
		printf("[ERROR] mutex initialization failiure\n");
		destroy_locks(table);
		return (-1);
	}
	return (0);
}

int	init_philosophers(t_table *table)
{
	int	i;

	i = 0;
	table->phil = malloc(sizeof(t_phil) * table->config.philosophers);
	table->fork = malloc(sizeof(pthread_mutex_t) * table->config.philosophers);
	if (!table->phil || !table->fork)
	{
		free_table(table);
		printf("heap allocation failure\n");
		return (-1);
	}
	table->init_time = get_time();
	while (i < table->config.philosophers)
	{
		table->phil[i].id = i + 1;
		table->phil[i].l_fork = i;
		table->phil[i].r_fork = (i + 1) % table->config.philosophers;
		table->phil[i].meal_counter = 0;
		table->phil[i].last_meal_time = table->init_time;
		table->phil[i].table = table;
		i++;
	}
	return (0);
}

int	init_table(t_table *table, int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		printf("%s usage: <deathtime> <eatingtime> <sleepingtime>\n", av[0]);
		return (-1);
	}
	table->config.philosophers = ft_atoi(av[1]);
	table->config.time_to_die = ft_atoi(av[2]);
	table->config.time_to_eat = ft_atoi(av[3]);
	table->config.time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		table->config.max_meals = ft_atoi(av[5]);
	else
		table->config.max_meals = -1;
	if (table->config.philosophers < 1 || table->config.time_to_die < 1
		|| table->config.time_to_eat < 1 || table->config.time_to_sleep < 1
		|| (ac == 6 && table->config.max_meals < 1))
	{
		printf("[ERROR] invalid input arguments.\n");
		return (-1);
	}
	table->completion_flag = 0;
	return (0);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (init_table(&table, ac, av) != 0)
		return (1);
	if (init_philosophers(&table))
		return (1);
	if (init_locks(&table))
		return (1);
	if (instantiate_philosophers(&table))
		return (1);
	init_monitor(&table);
}
