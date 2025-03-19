#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include "libft_extra.h"
#include "libft.h"



# define MIN_PHIL 2
# define MAX_PHIL 20

# define MIN_DIE 1
# define MAX_DIE 20

# define MIN_EAT 1
# define MAX_EAT 20

# define MIN_SLEEP 1
# define MAX_SLEEP 20

# define MIN_MEALS 1
# define MAX_MEALS 20

typedef struct s_phil
{
	int	id;
	int	is_eating;
	int meals_eaten;
	int is_alive;
	size_t last_meal;

	// probably something to keep track as well as pointers to neighbours etc
} t_phil;

typedef struct s_fork
{
	int	id;
} t_fork;

typedef struct s_settings
{
	int	n;
	int	time_to_die;
	int time_to_eat;
	int	time_to_sleep;
	int	meals_needed;
} t_settings;

typedef struct s_table
{
	t_phil *philosophers;
	t_fork *forks;
	t_settings *settings;
	size_t start_time;
} t_table;




void print_settings(const t_settings *settings);

t_instance *init_simulation_instance(t_settings *settings);
t_settings	*init_settings(int argc, char *argv[]);
size_t get_time();

#endif // PHILOSOPHERS_H
