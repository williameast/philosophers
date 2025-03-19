/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:09:14 by weast             #+#    #+#             */
/*   Updated: 2025/03/19 14:29:48 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include "philosophers.h"
#include <sys/time.h>

// get current time at ms precision
size_t get_time(void)
{
	struct timeval time;

	if (gettimeofday(&time, NULL) == -1)
		ft_putstr_fd("could not get time.", 2);
	return(time.tv_sec * 1000 + time.tv_usec / 1000);
}
