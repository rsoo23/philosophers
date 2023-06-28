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

void	*routine(void *philo)
{
	t_ph	*ph;

	ph = (t_ph *)(philo);
	while (1)
	{
		philo_take_forks(ph, ph->info, ph->ph_i);
		if (ph->die_status)
			break ;
		philo_eat(ph, ph->info, ph->ph_i);
		if (ph->die_status)
			break ;
		philo_sleep(ph, ph->info, ph->ph_i);
		if (ph->die_status)
			break ;
		philo_think(ph, ph->ph_i);
		if (ph->die_status)
			break ;
		if (ph->info->must_eat_num && ph->info->must_eat_num == ph->eat_num)
			break ;
	}
	return (NULL);
}

/*
if info is passed in via pthread_create, I would need the index to 
get the correct philo index, but it is updated before the routine
starts causing a data race

so I'll declare the philo[200] here instead of inside the struct
*/

void	check_any_ph_die(t_ph philo[200], t_info *info)
{
	int	i;

	i = -1;
	pthread_mutex_init(&info->die_lock, NULL);
	mod_usleep(info->t_eat, &philo[0]);
	while (!info->glob_die_status)
	{
		while (++i < info->ph_num)
		{
			printf("	check_ind: %d\n", i);
			check_if_dead(&philo[i], info, i);
		}
		// printf("	glob_ds:%d\n", info->glob_die_status);
	}
	pthread_mutex_destroy(&info->die_lock);
}

void	init_philo(t_ph philo[200], t_info *info)
{
	int	i;

	i = -1;
	info->glob_die_status = 0;
	init_timestamp(info);
	while (++i < info->ph_num)
	{
		philo[i].ph_i = i;
		philo[i].info = info;
		philo[i].eat_num = 0;
		philo[i].die_status = 0;
		philo[i].eat_st_time = 0;
		if (pthread_mutex_init(&info->fork[i], NULL))
			return ;
		if (pthread_create(&philo[i].th, NULL, &routine, (void *)(&philo[i])))
			return ;
	}
	check_any_ph_die(philo, info);
}

void	exit_philo(t_ph philo[200], t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->ph_num)
	{
		if (pthread_join(philo[i].th, NULL))
			return ;
		if (pthread_mutex_destroy(&info->fork[i]))
			return ;
	}
}

int main(int ac, char **av)
{
	t_info	info;
	t_ph	philo[200];

	if (ac < 5 || ac > 6 || !input_check_and_assign(av, &info))
		return (1);
	if (info.ph_num == 1)
	{
		printf("%07lld %d died\n", (long long)0, 1);
		return (0);
	}
	init_philo(philo, &info);
	exit_philo(philo, &info);
}
/*
thought process:

1. creates 5 threads
2. creates 5 mutexes?
3. 
*/
