/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 10:58:19 by William           #+#    #+#             */
/*   Updated: 2025/07/14 16:46:45 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"


static void	init_fork_array(t_table *table)
{
	int	i;

	table->forks = malloc(sizeof(t_fork) * table->phil_count);
	if (!table->forks)
		return ;
	i = 0;
	while (i < table->phil_count)
	{
		fork_init(&table->forks[i]);
		i++;
	}
}

void init_thread_array(t_table *table)
{
    int i;

    table->threads = malloc(sizeof(pthread_t) * table->phil_count);
    if (!table->threads)
    {
        fprintf(stderr, "Failed to allocate memory for threads\n");
        return;
    }

    i = 0;
    while (i < table->phil_count)
    {
        if (pthread_create(&table->threads[i], NULL, philosopher_routine, &table->phils[i]) != 0)
        {
            fprintf(stderr, "Failed to create thread for philosopher %d\n", i + 1);
            return;
        }
        i++;
    }
}

void join_philosopher_threads(t_table *table)
{
    int i = 0;
    while (i < table->phil_count)
    {
        pthread_join(table->threads[i], NULL);
        /* printf("Thread %d joined.\n", i + 1); */
        i++;
    }
    free(table->threads);
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
		table->phils[i].meals_consumed = kvp_init(0);
		table->phils[i].left = &table->forks[i];
		table->phils[i].right = &table->forks[(i + 1) % table->phil_count];
		table->phils[i].table = table;
		i++;
	}
}

t_table	*init_table(int ac, char **av)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->time_of_init = get_time();
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
	table->sim_ended = kvp_init(FALSE);
	init_fork_array(table);
	init_phil_array(table);
	return (table);
}
