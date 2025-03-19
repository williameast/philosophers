/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:46:37 by weast             #+#    #+#             */
/*   Updated: 2025/03/19 15:40:28 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"

int main(int argc, char *argv[])
{
	t_settings *settings;
	t_table *sim;
	settings = init_settings(argc, argv);
	if (!settings)
	{
		ft_putstr_fd("Invalid input or memory allocation failiure\n", 0);
		return 1;
	}
	sim = init_simulation_instance(settings);
	print_settings(sim->settings);
    return 0;
}
