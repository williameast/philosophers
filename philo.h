/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:37:08 by William           #+#    #+#             */
/*   Updated: 2025/07/14 15:33:25 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

// consts
# define MAX_PHILOSOPHERS 300
# define MIN_PHILOSOPHERS 0

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
# define FALSE 0

// CPU clock delay amount
# define CPU_DELAY_TIME 1000

// str consts;
# define FORK_TAKEN "has taken a fork"
# define DIED "died"

# define SLEEPING "is sleeping"
# define EATING "is eating"
# define THINKING "is thinking"

# define ERR_MUTEX "could not initialized mutex"

# define DEBUG_PHIL "Philosopher %d starting. Left fork: %p, Right fork: %p\n"

typedef struct s_kvp
{
	long long		value;
	pthread_mutex_t	lock;
}					t_kvp;

typedef struct s_fork
{
	t_kvp			*available;
}					t_fork;

typedef struct s_settings
{
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				max_meals;
}					t_settings;

typedef struct s_table
{
	t_fork			*forks;
	struct s_phil	*phils;
	int				phil_count;
	pthread_mutex_t	print_lock;
	t_kvp			*sim_ended;
	t_settings		settings;
	pthread_t		*threads;
	pthread_t		monitor_thread;
	long long		time_of_init;
}					t_table;

typedef struct s_phil
{
	int				id;
	t_kvp			*last_meal_time;
	t_kvp			*meals_consumed;
	t_fork			*left;
	t_fork			*right;
	t_table			*table;
}					t_phil;
// atox.c, functions for parsing input.
long long			ft_atoll(const char *str);
int					ft_atoi(const char *str);

// utils
long long			get_time(void);
long long			get_relative_time(t_table *sim);

// init functions
t_table				*init_table(int ac, char **av);

// forks
int					fork_init(t_fork *fork);
void				fork_destroy(t_fork *fork);
int					fork_is_available(t_fork *fork);
void				fork_set_available(t_fork *fork);
void				fork_set_busy(t_fork *fork);

// kvp handling

long long			kvp_get(t_kvp *kvp);
void				kvp_set(t_kvp *kvp, long long value);
t_kvp				*kvp_init(long long value);
void				kvp_destroy(t_kvp *kvp);

// philosophers

void				*philosopher_routine(void *arg);

// monitor
void *monitor_routine(void *arg);
int	init_monitor();
void init_thread_array();

// utils
void				log_state(t_table *table, int philo_id, char *msg);
int					validate_input(t_table *table, int ac);


void join_philosopher_threads(t_table *table);
void init_thread_array(t_table *table);


void	cleanup();
#endif // PHILO_H
