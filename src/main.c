/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 12:43:24 by William           #+#    #+#             */
/*   Updated: 2025/07/14 17:11:12 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <pthread.h>

int main(int ac, char **av)
{
    t_table *table;

    table = init_table(ac, av);
    if (!table)
        return 1;

    // Initialize monitor thread
    if (init_monitor(table) != 0)
    {
        // Handle error
        cleanup(table);
        return 1;
    }

    // Create philosopher threads
    init_thread_array(table);

    // Now join the monitor thread
    pthread_join(table->monitor_thread, NULL);
    // Join philosopher threads
    join_philosopher_threads(table);


    // Clean up
    cleanup(table);

    return 0;
}
