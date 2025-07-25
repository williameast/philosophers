/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:05:30 by weast             #+#    #+#             */
/*   Updated: 2025/07/22 10:53:50 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef enum e_actions
{
	EATING,
	SLEEPING,
	FORK_TAKEN,
	THINKING,
	DIED,
	FINISHED,
}					t_action;

typedef struct s_phil
{
	int				id;
	int				meal_counter;
	int				l_fork;
	int				r_fork;
	long long		last_meal_time;
	struct s_table	*table;
	pthread_t		thread;
	int				done_eating;
}					t_phil;

typedef struct s_settings
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_meals;
	int				philosophers;
}					t_settings;

typedef struct s_table
{
	t_phil			*phil;
	pthread_mutex_t	*fork;
	t_settings		config;
	int				meals_needed;
	int				completion_flag;
	long long		init_time;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	eat_lock;
	pthread_mutex_t	finish_lock;
	pthread_mutex_t	meal_count_lock;
}					t_table;

/* time controls */
void				tick(t_phil *phil, long long stop);
long long			get_time(void);
void				set_completion_flag(t_phil *phil, int status);
int					sim_is_running(t_phil *phil);

/* simulation functions */
void				print_action(t_phil *phil, int status);
void				*phil_routine(void *args);

/* monitor thread */
void				init_monitor(t_table *table);

/* utilities and io */
int					ft_atoi(const char *str);
void				print_special_status(t_phil *phil, int status);
void				print_normal_status(t_phil *phil, int status);

/* cleanup and error handling */
void				rejoin_threads(t_table *table);
void				destroy_locks(t_table *table);
void				free_table(t_table *table);

#endif // PHILO_H
