/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 12:40:36 by William           #+#    #+#             */
/*   Updated: 2025/06/18 12:45:08 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

void	destroy_table(t_table *sim)
{
	int	i;

	i = 0;
	while (i++ < sim->num_philosophers)
		pthread_mutex_destroy(&sim->forks[i].mutex);
	pthread_mutex_destroy(&sim->meal_lock);
	pthread_mutex_destroy(&sim->print_lock);
	free(sim->forks);
	free(sim->philosophers);
	/* free(sim); */
}
