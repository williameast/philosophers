/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:40:17 by weast             #+#    #+#             */
/*   Updated: 2025/03/19 15:40:08 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"

static int	convert_input(char *input, int min, int max)
{
	int	output;

	output = ft_atoi(input);
	if (output == 0 && input[0] != '0')
		return -1;
	if (output < min || output > max)
		return -1;
	return output;
}

// check that input is valid. if it is -1, then the input has failed
static int validate_settings(t_settings *s)
{
	return (s->n == -1
		|| s->time_to_die == -1
		|| s->time_to_eat == -1
		|| s->time_to_sleep == -1
		|| s->meals_needed == -1);
}


t_phil	*init_philosopher(int id, t_table *sim)
{
	t_phil *phil;

	phil->id = id;
	phil->is_eating = 0;
	phil->is_alive = 0;
	phil->meals_eaten = 0;
	phil->last_meal = sim->start_time;
	return (phil);
}

t_settings	*init_settings(int argc, char *argv[])
{
	t_settings *settings;

    if (argc != 5 && argc != 6)
        return NULL;
	settings = safe_malloc(sizeof(t_settings));
	settings->n = convert_input(argv[1], MIN_PHIL, MAX_PHIL);
	settings->time_to_die = convert_input(argv[2], MIN_DIE, MAX_DIE);
	settings->time_to_eat = convert_input(argv[3], MIN_EAT, MAX_EAT);
	settings->time_to_sleep = convert_input(argv[4], MIN_SLEEP, MAX_SLEEP);
	if (argc == 6)
		settings->meals_needed = convert_input(argv[5], MIN_MEALS, MAX_MEALS);
	else
		settings->meals_needed = -2;
	if (validate_settings(settings))
		return NULL;
	return (settings);
}

t_table *init_simulation_table(t_settings *settings)
{
	t_table *sim;

	sim = safe_malloc(sizeof(t_table));
	sim->settings = settings;
	sim->philosophers = safe_malloc(sizeof(t_phil) * sim->settings->n);
	sim->forks = safe_malloc(sizeof(t_phil) * sim->settings->n);
	sim->start_time = get_time();

	return (sim);
}
