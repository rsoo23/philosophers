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

// gcc -Wall -Wextra -Werror -pthread *.c

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

void	init_timestamp(t_info *info)
{
	struct timeval	start;

	gettimeofday(&(start), NULL);
	info->st_time = (long long)start.tv_sec * 1000 + start.tv_usec / 1000;
	// printf("%lld\n\n", info->st_time);
}

void	get_time(t_info *info)
{
	struct timeval	cur;

	gettimeofday(&cur, NULL);
	info->time = ((long long)cur.tv_sec * 1000 + cur.tv_usec / 1000) - info->st_time;
	// printf("%lld\n", info->time);
}

void	*routine(void *info)
{
	t_info	*in;
	int		ph_i;

	in = (t_info *)(info);
	ph_i = in->i;
	init_timestamp(in);
	get_time(in);
	while (1)
	{
		philo_eat(in, ph_i);
		philo_sleep(in, ph_i);
		philo_think(in, ph_i);
		if (in->must_eat_num == in->philo[ph_i].eat_num)
			return (NULL);
	}
	return (NULL);
}

void	init_philo(t_info *info)
{
	if (info->ph_num == 1)
		philo_dies(info, 1);
	info->think_st_time = 0;
	info->i = -1;
	while (++info->i < info->ph_num)
	{
		info->philo[info->i].eat_num = 0;
		if (pthread_mutex_init(&info->fork[info->i], NULL))
			return ;
		// printf("	fork %d is created\n", info->i + 1);
	}
	info->i = -1;
	while (++info->i < info->ph_num)
	{
		// printf("	i: %d\n", info->i);
		if (pthread_create(&info->philo[info->i].th, NULL, &routine, (void *)info))
			return ;
	}
}

void	end_philo(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->ph_num)
	{
		if (pthread_join(info->philo[i].th, NULL))
			return ;
		if (pthread_mutex_destroy(&info->fork[i]))
			return ;
	}
}

int main(int ac, char **av)
{
	t_info	info;

	if (ac < 5 || ac > 6 || !input_check_and_assign(av, &info))
		return (1);
	init_philo(&info);
	end_philo(&info);
}

/*
thought process:

1. creates 5 threads
2. creates 5 mutexes?
3. 
*/
