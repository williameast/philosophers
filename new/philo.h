/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:05:30 by weast             #+#    #+#             */
/*   Updated: 2025/07/16 15:59:28 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>


typedef enum e_actions
{
	EATING,
	SLEEPING,
	FORK_TAKEN,
	THINKING,
	DIED,
	FINISHED,
} t_action;

# define STR_FINISH "died"

typedef struct s_phil
{
	int				id;
	int				meal_counter;
	int				l_fork;
	int				r_fork;
	long long		last_meal_time;
	struct s_table	*table;
	pthread_t		thread;
}					t_phil;

typedef struct s_settings
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_meals;
	int				philosophers;
} t_settings;

typedef struct s_table
{
	t_phil		*phil;
	pthread_mutex_t *fork;
	t_settings	config;
	int			meals_needed;
	int			completion_flag;
	long long	init_time;
	pthread_mutex_t print_lock;
	pthread_mutex_t eat_lock;
	pthread_mutex_t finish_lock;
} t_table;


void	tick(t_phil *phil, long long stop);
long long	get_time(void);
void set_completion_flag(t_phil *phil, int status);
int	sim_is_running(t_phil *phil);
#endif // PHILO_H
