/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:41:11 by weast             #+#    #+#             */
/*   Updated: 2025/07/10 14:37:36 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "pthread.h"



int set_mutex_value(pthread_mutex_t *mutex, int *variable, int value)
{
    int result;

    if (pthread_mutex_lock(mutex) != 0)
        return (-1);
    *variable = value;
    result = *variable;
    if (pthread_mutex_unlock(mutex) != 0)
        return (-1);
    return (result);
}

int get_mutex_value(pthread_mutex_t *mutex, int *variable)
{
    int result;

    if (pthread_mutex_lock(mutex) != 0)
        return (-1);
    result = *variable;
    if (pthread_mutex_unlock(mutex) != 0)
        return (-1);
    return (result);
}

void	init_mutex(pthread_mutex_t *mutex)
{
	pthread_mutex_init(mutex, NULL);
}

void	destroy_mutex(pthread_mutex_t *mutex)
{
	&pthread_mutex_destroy(mutex);
}
