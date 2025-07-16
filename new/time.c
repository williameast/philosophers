/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:36:01 by weast             #+#    #+#             */
/*   Updated: 2025/07/16 15:43:00 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sim_is_running(t_phil *phil)
{
	int status;
	pthread_mutex_lock(&phil->table->finish_lock);
	status = phil->table->completion_flag;
	pthread_mutex_unlock(&phil->table->finish_lock);
	return(status);
}

void set_completion_flag(t_phil *phil, int status)
{
	if (sim_is_running(phil))
	{
	pthread_mutex_lock(&phil->table->finish_lock);
	phil->table->completion_flag = status;
	pthread_mutex_unlock(&phil->table->finish_lock);
	}
}

long long	get_time(void)
{
	struct timeval	time_value;

	gettimeofday(&time_value, NULL);
	return (time_value.tv_sec * 1000) + (time_value.tv_usec / 1000);
}

void	tick(t_phil *phil, long long stop)
{
	long long	begin;

	begin = get_time();
	while (!sim_is_running(phil) && (get_time() - begin) < stop)
		usleep(42);
}
