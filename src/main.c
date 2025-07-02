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
		return (1);
	}
	sim = init_table(ac, av);
	if (!sim)
	{
		fprintf(stderr, "could not init simulation\n");
		return (1);
	}
	DEBUG_PRINT("Program Started\n");

	init_forks(sim);
	init_monitor(sim);
	create_philosophers(sim);
	join_philosophers(sim);
	destroy_table(sim);

	return (0);
}
