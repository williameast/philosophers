/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kvp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:28:51 by weast             #+#    #+#             */
/*   Updated: 2025/07/11 16:31:44 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../philo.h"

/* create new key value pair, including a mutex lock. needs to be initialized
 * before it can be used. querying it should be safe!  */
// kvp.c

t_kvp	*kvp_init(long long value)
{
	t_kvp	*kvp;

	kvp = malloc(sizeof(t_kvp));
	if (!kvp)
		return (NULL);
	kvp->value = value;
	pthread_mutex_init(&kvp->lock, NULL);
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
