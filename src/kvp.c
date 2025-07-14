/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kvp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:28:51 by weast             #+#    #+#             */
/*   Updated: 2025/07/14 14:10:46 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../philo.h"

t_kvp	*kvp_init(long long value)
{
	t_kvp	*kvp;

	kvp = malloc(sizeof(t_kvp));
	if (!kvp)
		return (NULL);
	kvp->value = value;
	if (pthread_mutex_init(&kvp->lock, NULL))
	{
		printf(ERR_MUTEX);
		return (NULL);
	}
	return (kvp);
}

void	kvp_destroy(t_kvp *kvp)
{
	if (!kvp)
		return ;
	pthread_mutex_destroy(&kvp->lock);
	free(kvp);
}

long long	kvp_get(t_kvp *kvp)
{
	int	val;

	pthread_mutex_lock(&kvp->lock);
	val = kvp->value;
	pthread_mutex_unlock(&kvp->lock);
	return (val);
}

void	kvp_set(t_kvp *kvp, long long value)
{
	pthread_mutex_lock(&kvp->lock);
	kvp->value = value;
	pthread_mutex_unlock(&kvp->lock);
}
