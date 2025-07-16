/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:08:04 by weast             #+#    #+#             */
/*   Updated: 2025/07/16 16:55:16 by weast            ###   ########.fr       */
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
		if (pthread_create(&table->phil[i].thread, NULL, phil_routine, &table->phil[i]))
			exit(128);
			/* exit_error("Couldn't create thread", table, 3); */
		i++;
	}
	return (0);
}

void	init_locks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->config.philosophers)
	{
		if (pthread_mutex_init(&table->fork[i], NULL))
			/* exit_error("Couldn't init forks mutex", table, 2); */
			exit(128);
		i++;
	}
	if (pthread_mutex_init(&table->print_lock, NULL))
		/* exit_error("Couldn't init print mutex", table, 2); */
			exit(128);
	if (pthread_mutex_init(&table->eat_lock, NULL))
		/* exit_error("Couldn't init eat mutex", table, 2); */
			exit(128);
	if (pthread_mutex_init(&table->finish_lock, NULL))
		/* exit_error("Couldn't init finish mutex", table, 2); */
			exit(128);
}

void	init_philosophers(t_table *table)
{
	int	i;

	i = 0;
	table->phil = malloc(sizeof(t_phil) * table->config.philosophers);
	table->fork = malloc(sizeof(pthread_mutex_t) * table->config.philosophers);
	if (!table->phil || !table->fork)
		exit(128);
		/* exit_error("Couldn't create the philosophers and forks", table, 1); */
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
}

void	init_table(t_table *table, int ac, char **av)
{
	if (ac < 5 || ac > 6)
		exit(128);
		/* exit_error("Wrong number of arguments", NULL, 0); */
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
		exit(128);
		/* exit_error("Invalid arguments", NULL, 0); */
	table->completion_flag = 0;
}

int	main(int ac, char **av)
{
	t_table	table;

	puts("building table..");
	init_table(&table, ac, av);
	puts("building phils..");
	init_philosophers(&table);
	puts("building locks..");
	init_locks(&table);
	puts("initing phils");
	instantiate_philosophers(&table);
	init_monitor(&table);
}
