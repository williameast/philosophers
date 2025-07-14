/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:12:34 by William           #+#    #+#             */
/*   Updated: 2025/07/14 13:12:13 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../philo.h"

int	fork_init(t_fork *fork)
{
	fork->available = kvp_init(TRUE);
	return (1);
}

void	fork_destroy(t_fork *fork)
{
	if (!fork)
		return ;
	kvp_destroy(fork->available);
	free(fork);
}

int	fork_is_available(t_fork *fork)
{
	return (kvp_get(fork->available));
}

void	fork_set_available(t_fork *fork)
{
	kvp_set(fork->available, TRUE);
}

void	fork_set_busy(t_fork *fork)
{
	kvp_set(fork->available, FALSE);
}
