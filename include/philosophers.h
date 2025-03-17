#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <unistd.h>
#include "ft_printf.h"
#include "pthread.h"


typedef struct s_phil
{
	int	id;
	// probably something to keep track as well as pointers to neighbours etc
	int	has_eaten;
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

typedef struct s_instance
{
	t_phil *philosophers;
	t_fork *forks;
	int time;
} t_instance;


#endif // PHILOSOPHERS_H
