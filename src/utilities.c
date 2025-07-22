/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:11:58 by weast             #+#    #+#             */
/*   Updated: 2025/07/18 11:35:03 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <limits.h>

void	print_special_status(t_phil *phil, int status)
{
	long long	time;

	time = get_time() - phil->table->init_time;
	if (status == DIED)
		printf("%lld %d died\n", time, phil->id);
	else if (status == FINISHED)
		printf("%lld Simulation finished: all philosophers have eaten enough\n",
			time);
}

void	print_normal_status(t_phil *phil, int status)
{
	long long	time;
	char		*msg;

	if (status == EATING)
		msg = "is eating";
	else if (status == SLEEPING)
		msg = "is sleeping";
	else if (status == THINKING)
		msg = "is thinking";
	else if (status == FORK_TAKEN)
		msg = "has taken a fork";
	else
		msg = "ERROR";
	time = get_time() - phil->table->init_time;
	printf("%lld %d %s\n", time, phil->id, msg);
}

static int	check_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v'
		|| c == '\f');
}

static int	check_int_overflow(long res, int sign)
{
	if (sign == 1 && res > INT_MAX)
		return (0);
	else if (sign == -1 && - res < INT_MIN)
		return (0);
	else
		return (1);
}

int	ft_atoi(const char *str)
{
	long			res;
	long			sign;
	unsigned int	i;

	res = 0;
	sign = 1;
	i = 0;
	while (check_whitespace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i++] - '0';
		if (!check_int_overflow(res, sign))
			return (0);
	}
	return ((int)(res * sign));
}
