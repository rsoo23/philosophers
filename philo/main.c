/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:55:54 by rsoo              #+#    #+#             */
/*   Updated: 2023/06/12 15:55:54 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// gcc -Wall -Wextra -Werror -pthread main.c

/*
pthread_join:
- when thread is created, it is split into the: new thread and main thread
- pthread_join causes the main thread to wait until the new thread is complete
pthread_join: like a wait function for threads

pthread_mutex_lock + unlock (mutual exclusive):
- when a thread has this, it makes sure that no other thread is going to execute
- preventing race conditions

pthread_detach vs pthread_join
- detached thread:
	- automatically releases it resources when it terminates
	- can't join it back using pthread_join
	- used for tasks that run independently and don't need to be synchronised with
	  the main thread / other threads
- join:
	- used to wait for a thread to terminate and obtain its exit status
	- when a thread is joined, the calling thread will be blocked until the specified 
	thread finishes executing 
- they are both used in different scenarios: depending on whether you need to wait
for the thread to finish and obtain its exit status / if the thread can be left to run 
independently without the need for joining
- summary: detached threads and main thread run concurrently, pthread_join stops the main
thread, runs the threads, then goes back to the main thread once it is done

deadlocks:
- when you try and lock a mutex twice
- keep in mind of the order in which you lock and unlock the mutexes
*/


void	*routine(void *info)
{
	t_info	*in;
	
	in = (t_info *)(info);
	while (1)
	{
		if (in->philo[in->ph_i].state = 'e')
			philo_eat(in);
		else if (in->philo[in->ph_i].state = 's')
			philo_sleep(in);
		else if (in->philo[in->ph_i].state = 't')
			philo_think(in);
	}
}

void	init_philo(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->ph_num)
	{
		info->philo->state = 'e';
		info->philo->eat_num = 0;
	}
	info->time = 0;
}

int main(int ac, char **av)
{
	t_info	info;
	int		*res;

	if (ac < 5 || ac > 6 || !input_check_and_assign(av, &info))
		return (1);
	init_philo(&info);
	info.ph_i = -1;
	while (++info.ph_i < info.ph_num)
	{
		if (pthread_mutex_init(&info.fork[info.ph_i], NULL))
			return (1);
		if (pthread_create(&info.philo[info.ph_i], NULL, &routine, (void *)&info))
			return (1);
	}
	info.ph_i = -1;
	while (++info.ph_i < info.ph_num)
	{
		if (pthread_join(&info.philo[info.ph_i], NULL))
			return (1);
		if (pthread_mutex_destroy(&info.fork[info.ph_i]))
			return (1);
	}
}

/*
thought process:

1. creates 5 threads
2. creates 5 mutexes?
3. 
*/
