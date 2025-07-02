/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:12:34 by William           #+#    #+#             */
/*   Updated: 2025/07/02 11:58:22 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"
#include <pthread.h>

void init_forks(t_table *sim)
{
    int i;

    i = 0;
    while (i < sim->num_philosophers)
    {
        pthread_mutex_init(&sim->forks[i].mutex, NULL);
        i++;
    }
}
// take a for left, and right
// TODO explain why the modulo thing happens.
// lock the forks, print message (which locks print)
void take_forks(t_table *sim, int philo_id)
{
	int left_fork = philo_id;
	int right_fork = (philo_id + 1) % sim->num_philosophers;

	pthread_mutex_lock(&sim->forks[left_fork].mutex);
	print_status(sim, philo_id, FORK_TAKEN);
	pthread_mutex_lock(&sim->forks[right_fork].mutex);
	print_status(sim, philo_id, FORK_TAKEN);
}

// put the forks back (freeing them for use)
void	put_forks(t_table *sim, int philo_id)
{
	int left_fork = philo_id;
	int right_fork = (philo_id + 1) % sim->num_philosophers;

	pthread_mutex_unlock(&sim->forks[left_fork].mutex);
	pthread_mutex_unlock(&sim->forks[right_fork].mutex);
}
