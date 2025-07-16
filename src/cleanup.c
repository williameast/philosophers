/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 14:37:48 by William           #+#    #+#             */
/*   Updated: 2025/07/15 18:36:06 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <pthread.h>



void destroy_fork(t_fork *fork)
{
    puts("removing fork kvp...");
	kvp_destroy(&fork->available); // Cleanly destroy the kvp
    puts("removed fork kvp");
}

void	cleanup(t_table *table)
{
	int	i;

	puts("cleaning up");
	
	// Clean up philosophers
	for (i = 0; i < table->num_philosophers; i++)
	{
		kvp_destroy(&table->phil[i].last_meal_time);
		kvp_destroy(&table->phil[i].meals_consumed);
	}
	free(table->phil);
	
	// Clean up forks
	for (i = 0; i < table->num_philosophers; i++)
		destroy_fork(&table->fork[i]);
	free(table->fork);
	
	// Clean up table
	kvp_destroy(&table->print_lock);
	free(table);
}
