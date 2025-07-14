/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 10:58:19 by William           #+#    #+#             */
/*   Updated: 2025/07/12 00:58:35 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"


static void	init_fork_array(t_table *table)
{
	int	i;

	table->forks = malloc(sizeof(t_fork) * table->phil_count);
	if (!table->forks)
		return ;
	while (i < table->phil_count)
	{
		fork_init(&table->forks[i]);
		i++;
	}
}

static void	init_thread_array(t_table *table)
{
	pthread_t	*threads;
	int			i;

	threads = malloc(sizeof(pthread_t) * table->phil_count);
	if (!threads)
		return ;
	i = 0;
	while (i < table->phil_count)
	{
		if (pthread_create(&threads[i], NULL, philosopher_routine,
				&table->phils[i]) != 0)
			return ;
		i++;
	}
	while (i < table->phil_count)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

static void	init_phil_array(t_table *table)
{
	int	i;

	table->phils = malloc(sizeof(t_phil) * table->phil_count);
	if (!table->phils)
	{
		free(table->forks);
		free(table);
		return ;
	}
	i = 0;
	while (i < table->phil_count)
	{
		table->phils[i].last_meal_time = kvp_init(table->time_of_init);
		table->phils[i].id = i + 1;
		table->phils[i].meals_consumed = 0;
		table->phils[i].left = &table->forks[i];
		table->phils[i].right = &table->forks[(i + 1) % table->phil_count];
		i++;
	}
}

t_table	*init_table(int ac, char **av)
{
	t_table	*table;
	int		i;

	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->phil_count = ft_atoi(av[1]);
	table->settings.time_to_die = ft_atoll(av[2]);
	table->settings.time_to_eat = ft_atoll(av[3]);
	table->settings.time_to_sleep = ft_atoll(av[4]);
	if (ac == 6)
		table->settings.max_meals = ft_atoi(av[5]);
	else
		table->settings.max_meals = -1;
	if (validate_input(table, ac))
		return (NULL);
	table->time_of_init = get_time();
	init_fork_array(table);
	init_phil_array(table);
	init_thread_array(table);
	return (table);
}
