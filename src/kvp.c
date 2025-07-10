/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kvp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:28:51 by weast             #+#    #+#             */
/*   Updated: 2025/07/10 15:10:11 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../philo.h"


void	init_kvp(t_kvp *kvp)
{
	init_mutex(&kvp->lock);
}

// TODO handle the case where a lock fails?
void	set_kvp(t_kvp *kvp, int value)
{
	int res;
    res = set_mutex_value(&kvp->lock, &kvp->value, value);
	if (res == -1)
		DEBUG_PRINT("value could not be set.\n");
}

int		get_kvp(t_kvp *kvp)
{
	int res;

	res = get_mutex_value(&kvp->lock, &kvp->value);
	if (res == -1)
		DEBUG_PRINT("value could not be set.\n");
	return res;
}
