/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 10:58:19 by William           #+#    #+#             */
/*   Updated: 2025/07/02 12:23:02 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	validate_input(t_table *sim, int ac)
{
	return (sim->num_philosophers <= MIN_PHILOSOPHERS
		|| sim->num_philosophers > MAX_PHILOSOPHERS
		|| sim->time_to_die <= MIN_DIE || sim->time_to_die > MAX_DIE
		|| sim->time_to_eat <= MIN_EAT || sim->time_to_eat > MAX_EAT
		|| sim->time_to_sleep <= MIN_SLEEP || sim->time_to_sleep > MAX_SLEEP
		|| (ac == 6 && sim->min_meals <= MIN_MEALS));
}

static void	init_philosophers(t_table *sim)
{
	int		i;
	t_phil	*phil;

	i = 0;
	while (i < sim->num_philosophers)
	{
		phil = &sim->philosophers[i];
		phil->id = i;
		phil->last_meal_time = 0;
		phil->meals_consumed = 0;
		i++;
	}
}


t_table	*init_table(int ac, char **av)
{
	t_table	*sim;

	sim = malloc(sizeof(t_table));
	if (!sim)
		return (NULL);
	sim->num_philosophers = ft_atoi(av[1]);
	sim->time_to_die = ft_atoll(av[2]);
	sim->time_to_eat = ft_atoll(av[3]);
	sim->time_to_sleep = ft_atoll(av[4]);
	if (ac == 6)
		sim->min_meals = ft_atoi(av[5]);
	else
		sim->min_meals = -1;
	if (validate_input(sim, ac))
		return (NULL);
	sim->forks = malloc(sizeof(t_fork) * sim->num_philosophers);
	sim->philosophers = malloc(sizeof(t_phil) * sim->num_philosophers);
	if (!sim->forks || !sim->philosophers)
	{
		destroy_table(sim);
		return (NULL);
	}
	pthread_mutex_init(&sim->meal_lock, NULL);
	pthread_mutex_init(&sim->print_lock, NULL);
	sim->start_time = get_time();
	init_philosophers(sim);
	sim->stop_simulation = FALSE;
	return (sim);
}
