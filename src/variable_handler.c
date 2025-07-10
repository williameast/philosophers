/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:11:01 by weast             #+#    #+#             */
/*   Updated: 2025/07/10 14:25:11 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "pthread.h"
#include <bits/pthreadtypes.h>

// key value pair (lockable)
typedef struct s_kvp
{
	int	value;
	pthread_mutex_t lock;
} t_kvp

typedef struct s_table
{
	int				num_philosophers;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				min_meals;
	long long		start_time;
	int				stop_simulation;
}					t_table;


int is_end(t_table *sim)
{
	int value;
	get_mutex_value(sim->locks[end_lock], )

}

int is_end(t_data *data)
{
    int result;
    pthread_mutex_lock(&data->mutex_locks[lock_end]);
    result = data->end;
    pthread_mutex_unlock(&data->mutex_locks[lock_end]);
    return (result);
}
void    set_end(t_data *data)
{
    pthread_mutex_lock(&data->mutex_locks[lock_end]);
    data->end = 1;
    pthread_mutex_unlock(&data->mutex_locks[lock_end]);
}
