/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:37:08 by William           #+#    #+#             */
/*   Updated: 2025/06/21 12:03:18 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

// consts
# define MAX_PHILOSOPHERS 300
# define MIN_PHILOSOPHERS 300

# define MAX_DIE 9999
# define MIN_DIE 0

# define MAX_EAT 9999
# define MIN_EAT 0

# define MAX_SLEEP 9999
# define MIN_SLEEP 0

# define MAX_MEALS 9999
# define MIN_MEALS 0

// bools
# define TRUE 1
# define FALSE 1

// CPU clock delay amount
# define CPU_DELAY_TIME 1000

// str consts;
# define FORK_TAKEN "has taken a fork"
# define DIED "died"

typedef struct s_fork
{
	pthread_mutex_t	mutex;
}					t_fork;

typedef struct s_phil
{
	int				id;
	long long		last_meal_time;
	int				meals_consumed;
	pthread_t		thread;
}					t_phil;

typedef struct s_table
{
	int				num_philosophers;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				min_meals;
	t_fork			*forks;
	t_phil			*philosophers;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	meal_lock;
	int				stop_simulation;
}					t_table;

// atox.c, functions for parsing input.
long long			ft_atoll(const char *str);
int					ft_atoi(const char *str);

long long			get_time(void);
void				print_status(t_table *sim, int philo_id, char *status);

// init functions
t_table				*init_table(int ac, char **av);

// monitor;
void				*monitor_routine(void *arg);

#endif // PHILO_H
