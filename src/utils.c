/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:36:24 by William           #+#    #+#             */
/*   Updated: 2025/07/02 12:29:22 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_table *sim, int philo_id, char *status)
{
	pthread_mutex_lock(&sim->print_lock);
	if (!sim->stop_simulation)
		printf("%lld %d %s\n", get_relative_time(sim), philo_id + 1, status);
	pthread_mutex_unlock(&sim->print_lock);
}

long long	get_time(void)
{
	struct timeval	time_value;

	gettimeofday(&time_value, NULL);
	return (time_value.tv_sec * 1000LL) + (time_value.tv_usec / 1000);
}

long long	get_relative_time(t_table *sim)
{
	return get_time() - sim->start_time;
}
