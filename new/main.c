/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:08:04 by weast             #+#    #+#             */
/*   Updated: 2025/07/16 16:01:01 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>



void	print_action(t_phil *phil, int status)
{
	long long	time;
	char *msg;

	pthread_mutex_lock(&phil->table->print_lock);
	if (!sim_is_running(phil))
	{
		if (status == EATING)
			msg = "is eating";
		else if (status == SLEEPING)
			msg = "is sleeping";
		else if (status == THINKING)
			msg = "is thinking";
		else if (status == FORK_TAKEN)
		msg = "has taken a fork";
		time = get_time() - phil->table->init_time;
		printf("%lld %d %s\n", time, phil->id, msg);
	}
	pthread_mutex_unlock(&phil->table->print_lock);
	if (status == DIED)
		printf("%d died\n", phil->id);
	if (status == FINISHED)
		printf("Simulation over. all have eaten enough\n!");
}

void	eating(t_phil *phil)
{
	if (phil->id % 2 == 0)
	{
		pthread_mutex_lock(&phil->table->fork[phil->l_fork]);
		pthread_mutex_lock(&phil->table->fork[phil->r_fork]);
	}
	else
	{
		pthread_mutex_lock(&phil->table->fork[phil->r_fork]);
		pthread_mutex_lock(&phil->table->fork[phil->l_fork]);
	}
	print_action(phil, FORK_TAKEN);
	print_action(phil, FORK_TAKEN);
	print_action(phil, EATING);
	tick(phil, phil->table->config.time_to_eat);
	pthread_mutex_lock(&phil->table->eat_lock);
	phil->meal_counter++;
	phil->last_meal_time = get_time();
	pthread_mutex_unlock(&phil->table->eat_lock);
	pthread_mutex_unlock(&phil->table->fork[phil->r_fork]);
	pthread_mutex_unlock(&phil->table->fork[phil->l_fork]);
}

void	*start_dinner(void *args)
{
	t_phil	*phil;

	phil = (t_phil *)args;
	if (phil->id % 2 == 0)
		usleep(phil->table->config.time_to_eat * 1000);
	while (1)
	{
		/* if (phil->table->config.philosophers == 1) */
		/* { */
		/* 	lone_philosopher(phil->table); */
		/* 	return (0); */
		/* } */
		if (sim_is_running(phil))
			return (0);
		eating(phil);
		print_action(phil, SLEEPING);
		tick(phil, phil->table->config.time_to_sleep);
		print_action(phil, THINKING);
		if (phil->table->config.philosophers % 2 != 0
			&& phil->table->config.philosophers <= 127)
			tick(phil, phil->table->config.time_to_eat);
	}
	return (0);
}

int	lone_philosopher(t_table *table)
{
	print_action(&table->philo[0], TAKE);
	advance_time(&table->philo[0], table->time_to_die);
	print_action(&table->philo[0], DIE);
	is_time_to_finish(&table->philo[0], YES);
	return (0);
}

int	check_if_dead_or_full(t_phil *phil)
{
	pthread_mutex_lock(&phil->table->eat_lock);
	if (get_time() - phil->last_meal_time >= phil->table->config.time_to_die)
	{
		print_action(phil, DIED);
		set_completion_flag(phil, 1);
		pthread_mutex_unlock(&phil->table->eat_lock);
		return (1);
	}
	else if (phil->table->config.max_meals > 0
		&& phil->meal_counter >= phil->table->config.max_meals)
	{
		phil->table->meals_needed++;
		if (phil->table->meals_needed >= phil->table->config.philosophers)
		{
			set_completion_flag(phil, 1);
			print_action(phil, FINISHED);
			pthread_mutex_unlock(&phil->table->eat_lock);
			return (1);
		}
	}
	pthread_mutex_unlock(&phil->table->eat_lock);
	return (0);
}
