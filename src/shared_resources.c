/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared_resources.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 14:07:26 by William           #+#    #+#             */
/*   Updated: 2025/07/15 16:05:48 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"


void	fork_init(t_fork *fork)
{
	kvp_set(&fork->available, TRUE);
}

void	fork_destroy(t_fork *fork)
{
	if (!fork)
		return ;
	kvp_destroy(&fork->available);
	free(fork);
}
int	fork_is_available(t_fork *fork)
{
	return (kvp_get(&fork->available));
}

void	fork_set_available(t_fork *fork)
{
	kvp_set(&fork->available, TRUE);
}

void	fork_set_busy(t_fork *fork)
{
	kvp_set(&fork->available, FALSE);
}

// New functions for handling both forks
int	take_left_fork(t_phil *phil)
{
	if (fork_is_available(phil->left_fork))
	{
		fork_set_busy(phil->left_fork);
		return (1);
	}
	return (0);
}

int	take_right_fork(t_phil *phil)
{
	if (fork_is_available(phil->right_fork))
	{
		fork_set_busy(phil->right_fork);
		return (1);
	}
	return (0);
}

void	release_left_fork(t_phil *phil)
{
	fork_set_available(phil->left_fork);
}

void	release_right_fork(t_phil *phil)
{
	fork_set_available(phil->right_fork);
}

int	take_both_forks(t_phil *phil)
{
	// Try to take left fork first
	if (!take_left_fork(phil))
		return (0);
	
	// Try to take right fork
	if (!take_right_fork(phil))
	{
		// If we can't take right fork, release left fork
		release_left_fork(phil);
		return (0);
	}
	
	return (1);
}

void	release_both_forks(t_phil *phil)
{
	release_left_fork(phil);
	release_right_fork(phil);
}
