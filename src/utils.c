/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:36:24 by William           #+#    #+#             */
/*   Updated: 2025/07/12 00:59:19 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"


void log_state(t_table *table, int philo_id, char *msg)
{
	pthread_mutex_lock(&table->print_lock);
	if (!kvp_get(&table->sim_ended))
		printf("%lld %d %s\n", get_relative_time(table), philo_id + 1, msg);
	pthread_mutex_unlock(&table->print_lock);
}

long long	get_time(void)
{
	struct timeval	time_value;

	gettimeofday(&time_value, NULL);
	return (time_value.tv_sec * 1000LL) + (time_value.tv_usec / 1000);
}

long long	get_relative_time(t_table *sim)
{
	return get_time() - sim->time_of_init;
}


int	validate_input(t_table *table, int ac)
{
	return (table->phil_count <= MIN_PHILOSOPHERS
		|| table->phil_count > MAX_PHILOSOPHERS
		|| table->settings.time_to_die <= MIN_DIE
		|| table->settings.time_to_die > MAX_DIE
		|| table->settings.time_to_eat <= MIN_EAT
		|| table->settings.time_to_eat > MAX_EAT
		|| table->settings.time_to_sleep <= MIN_SLEEP
		|| table->settings.time_to_sleep > MAX_SLEEP || (ac == 6
			&& table->settings.max_meals <= MIN_MEALS));
}
