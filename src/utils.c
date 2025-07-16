/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 11:57:46 by William           #+#    #+#             */
/*   Updated: 2025/07/15 18:50:38 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long long	get_time(void)
{
	struct timeval	time_value;

	gettimeofday(&time_value, NULL);
	return (time_value.tv_sec * 1000LL) + (time_value.tv_usec / 1000);
}

static void print_operation(t_kvp *lock, void *context)
{
    (void)lock; // Suppress unused parameter warning
    t_phil *phil = (t_phil *)context;
	char *msg;

	if (phil->state == EATING)
		msg = "is eating";
	else if (phil->state == SLEEPING)
		msg = "is sleeping";
	else if (phil->state == THINKING)
		msg = "is thinking";
	else if (phil->state == DYING)
		msg = "died";
	else
		msg = "ERR UNKNOWN";

    // Construct and print the log message
    printf("%lld philosopher %d %s\n",
           get_time() - phil->table->init_time,
           phil->id + 1,
		   msg);
}

void log_action(t_kvp *print_lock, t_phil *phil)
{
    kvp_access(print_lock, print_operation, (void *)phil);
}
