/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 14:49:00 by weast             #+#    #+#             */
/*   Updated: 2025/03/17 15:11:32 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>

int balance = 0;


// write balance after 0.25 second
void write_balance(int new_balance)
{
	usleep(250000);
	balance = new_balance;
}

// read balance after 0.25 second
int	read_balance()
{
	usleep(250000);
	return balance;
}


void	*deposit(void *amount)
{
	pthread_mutex_lock(&mutex);

	int account_balance = read_balance();

	account_balance += *((int *) amount);

	write_balance(account_balance);
	pthread_mutex_unlock(&mutex);
	return NULL;
}

int	main()
{
	pthread_mutex_t mutex;
	int before = read_balance();
	ft_printf("Before: %i\n", before);

	// create two threads to deposit using deposit function
	pthread_t t1;
	pthread_t t2;

	pthread_mutex_init(&mutex, NULL);

	int deposit1 = 300;
	int deposit2 = 200;


	pthread_create(&t1, NULL, deposit, (void*) &deposit1);
	pthread_create(&t2, NULL, deposit, (void*) &deposit2);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	pthread_mutex_destroy(&mutex);

	int	after = read_balance();
	ft_printf("after: %i\n", after);
	return 0;
}
