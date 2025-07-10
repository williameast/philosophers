/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:12:34 by William           #+#    #+#             */
/*   Updated: 2025/07/10 15:12:41 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../philo.h"
#include <pthread.h>

void init_forks(t_table *sim)
{
    int i;

    i = 0;
    while (i < sim->settings.num_philosophers)
    {
        init_mutex(sim->forks[i]->available);
        i++;
    }
}
// take a for left, and right
// TODO explain why the modulo thing happens.
// lock the forks, print message (which locks print)
void take_forks(t_table *sim, int philo_id)
{
	// philo_id is 0-based, matches fork array indices
	int left_fork = philo_id;
	int right_fork = (philo_id + 1) % sim->num_philosophers;

	// Prevent deadlock: odd philosophers take right fork first, even take left first
	if (philo_id % 2 == 0)
	{
		pthread_mutex_lock(&sim->forks[left_fork].mutex);
        DEBUG_PRINT("Philosopher %d locked left fork %d\n", philo_id, left_fork);
		print_status(sim, philo_id, FORK_TAKEN);
		if (sim->stop_simulation) {
			pthread_mutex_unlock(&sim->forks[left_fork].mutex);
			return;
		}
		pthread_mutex_lock(&sim->forks[right_fork].mutex);
        DEBUG_PRINT("Philosopher %d locked right fork %d\n", philo_id, right_fork);
		print_status(sim, philo_id, FORK_TAKEN);
	}
	else
	{
		pthread_mutex_lock(&sim->forks[right_fork].mutex);
        DEBUG_PRINT("Philosopher %d locked right fork %d\n", philo_id, right_fork);
		print_status(sim, philo_id, FORK_TAKEN);
		if (sim->stop_simulation) {
			pthread_mutex_unlock(&sim->forks[right_fork].mutex);
			return;
		}
		pthread_mutex_lock(&sim->forks[left_fork].mutex);
        DEBUG_PRINT("Philosopher %d locked left fork %d\n", philo_id, left_fork);
		print_status(sim, philo_id, FORK_TAKEN);
	}
}

// put the forks back (freeing them for use)
void	put_forks(t_table *sim, int philo_id)
{
	int left_fork = philo_id;
	int right_fork = (philo_id + 1) % sim->num_philosophers;

	pthread_mutex_unlock(&sim->forks[left_fork].mutex);
    DEBUG_PRINT("Philosopher %d unlocked left fork %d\n", philo_id, left_fork);
	pthread_mutex_unlock(&sim->forks[right_fork].mutex);
    DEBUG_PRINT("Philosopher %d unlocked right fork %d\n", philo_id, right_fork);
}
