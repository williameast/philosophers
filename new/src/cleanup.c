/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 10:36:51 by William           #+#    #+#             */
/*   Updated: 2025/07/17 10:53:15 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	free_table(t_table *table)
{
	free(table->phil);
	free(table->fork);
}

void	destroy_locks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->config.philosophers)
	{
		pthread_mutex_destroy(&table->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&table->print_lock);
	pthread_mutex_destroy(&table->eat_lock);
	pthread_mutex_destroy(&table->finish_lock);
	free_table(table);
}

void	rejoin_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->config.philosophers)
	{
		pthread_join(table->phil[i].thread, NULL);
		i++;
	}
	destroy_locks(table);
}
