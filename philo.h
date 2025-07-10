/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:37:08 by William           #+#    #+#             */
/*   Updated: 2025/07/02 12:46:25 by weast            ###   ########.fr       */
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
	struct s_table	*sim;
}					t_phil;

typedef struct s_table
{
	int				num_philosophers;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				min_meals;
	long long		start_time;
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
long long			get_relative_time(t_table *sim);
void				print_status(t_table *sim, int philo_id, char *status);

// init functions
t_table				*init_table(int ac, char **av);

// monitor;
void				*monitor_routine(void *arg);

// forks

void init_forks(t_table *sim);
void take_forks(t_table *sim, int philo_id);
void	put_forks(t_table *sim, int philo_id);

// philosophers

void create_philosophers(t_table *sim);
void join_philosophers(t_table *sim);

// monitor

void init_monitor(t_table *sim);

// cleanup

void destroy_table(t_table *sim);


#ifdef DEBUG
#define DEBUG_PRINT(...) do { \
    printf("[DEBUG] "); \
    printf(__VA_ARGS__); \
    fflush(stdout); \
} while (0)
#else
#define DEBUG_PRINT(...) do {} while (0)
#endif


#endif // PHILO_H
