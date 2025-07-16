/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 13:26:00 by William           #+#    #+#             */
/*   Updated: 2025/07/16 10:36:29 by William          ###   ########.fr       */
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

# define MAX_DIE 1000
# define MIN_DIE 0

# define MAX_EAT 9999
# define MIN_EAT 0

# define MAX_SLEEP 9999
# define MIN_SLEEP 0

# define MAX_MEALS 10
# define MIN_MEALS 0

// bools
# define TRUE 1
# define FALSE 0

// str consts;
# define FORK_TAKEN "has taken a fork"
# define DIED "died"

// sharable resource.
typedef struct s_kvp
{
	long long		value;
	pthread_mutex_t	lock;
}					t_kvp;

typedef struct s_fork
{
	t_kvp			available;
}					t_fork;

typedef enum e_phil_state
{
	EATING,
	SLEEPING,
	THINKING,
	DYING
}					t_phil_state;

typedef struct s_settings
{
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				max_meals;
}					t_settings;

// each phil has their id,
/* a thread allocated to them and a link to the table they are on. */
typedef struct s_phil
{
	int				id;
	pthread_t		thread;
	t_fork			*left_fork;
	t_fork			*right_fork;
	struct s_table	*table;
	int				state;
	t_kvp			meals_consumed;
	t_kvp			last_meal_time;
}					t_phil;

// a table has an array of philosophers, and the start of the sim.
typedef struct s_table
{
	t_phil			*phil;
	t_fork			*fork;
	int				num_philosophers;
	long long		init_time;
	t_kvp			print_lock;
	pthread_t		mon_thread;
	int				death_detected;
	t_settings		settings;
}					t_table;

// utils.c

long long			get_time(void);

// init functions
//
int				init_table(t_table *table, int ac, char **av);
t_phil				*init_philosopher(t_table *table, int id);
t_phil				*init_philosophers(t_table *table, t_fork *forks, int num_philosophers);
t_fork				*init_forks(int num_forks);
void				distribute_forks(t_phil *philosophers, t_fork *forks, int num_philosophers);

int					launch_philosophers(t_table *table);
int					launch_philosopher(t_phil *phil);
int					launch_monitor(t_table *table);
void				action(t_phil *phil, int delay);

void				log_action(t_kvp *print_lock, t_phil *phil);

void				*phil_lifecycle(void *arg);

void				dying(t_phil *phil);
// forks
t_fork				*init_fork(void);

void				fork_destroy(t_fork *fork);
int					fork_is_available(t_fork *fork);
void				fork_set_available(t_fork *fork);
void				fork_set_busy(t_fork *fork);

// New fork handling functions for dining philosophers
int					take_left_fork(t_phil *phil);
int					take_right_fork(t_phil *phil);
void				release_left_fork(t_phil *phil);
void				release_right_fork(t_phil *phil);
int					take_both_forks(t_phil *phil);
void				release_both_forks(t_phil *phil);

// kvp handling

long long			kvp_get(t_kvp *kvp);
void				kvp_set(t_kvp *kvp, long long value);
int					kvp_init(t_kvp *kvp, long long value);
void				kvp_destroy(t_kvp *kvp);
void				kvp_access(t_kvp *kvp, void (*operation)(t_kvp *, void *),
						void *context);

// clean
void				cleanup(t_table *table);

#endif // PHILO_H
