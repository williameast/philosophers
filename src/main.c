/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 12:43:24 by William           #+#    #+#             */
/*   Updated: 2025/07/02 12:42:31 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
    DEBUG_PRINT("Program started with %d arguments\n", ac);
	t_table *sim;
	if (!(ac == 5 || ac == 6))
	{
		fprintf(stderr, "incorrect args\n");
        DEBUG_PRINT("Incorrect args\n");
		return (1);
	}
	sim = init_table(ac, av);
	if (!sim)
	{
		fprintf(stderr, "could not init simulation\n");
        DEBUG_PRINT("Could not init simulation\n");
		return (1);
	}
	DEBUG_PRINT("Simulation initialized\n");

	init_forks(sim);
    DEBUG_PRINT("Forks initialized\n");
	init_monitor(sim);
    DEBUG_PRINT("Monitor initialized\n");
	create_philosophers(sim);
    DEBUG_PRINT("Philosopher threads created\n");
    usleep(100000); // Small delay to allow threads to start
	join_philosophers(sim);
    DEBUG_PRINT("Philosopher threads joined\n");
	destroy_table(sim);
    DEBUG_PRINT("Simulation destroyed and exiting\n");

	exit(0); // Ensure clean exit
	return (0);
}
