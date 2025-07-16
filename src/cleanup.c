/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 14:37:48 by William           #+#    #+#             */
/*   Updated: 2025/07/16 11:37:50 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <pthread.h>



void destroy_fork(t_fork *fork)
{
	kvp_destroy(&fork->available); // Cleanly destroy the kvp
}

void	cleanup(t_table *table)
{
	int	i;

	puts("cleaning up");

	for (i = 0; i < table->num_philosophers; i++)
	{
		kvp_destroy(&table->phil[i].last_meal_time);
		kvp_destroy(&table->phil[i].meals_consumed);
	}
	free(table->phil);
	for (i = 0; i < table->num_philosophers; i++)
		kvp_destroy(&table->fork[i].available);
	free(table->fork);
	kvp_destroy(&table->print_lock);
	free(table);
}
