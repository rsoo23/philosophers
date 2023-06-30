/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 22:00:34 by rsoo              #+#    #+#             */
/*   Updated: 2023/06/18 22:00:34 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// Notes:
// sem_wait(): 
// - if s == 0, it no longer can be decremented, 
// the thread will wait on that semaphore 
// - if s > 0, it decrements (s--) and executes
// sem_post():
// - increments the semaphore (s++) once it is done executing

// semaphores are basically mutexes with a counter
// -: sem_wait()
// p: print
// +: sem_post()
// if sem == 1
// T0  | . - p +
// T1  | . . . . - p + 
// T2  | . . . . . . . - p +
// T3  | . . . . . . . . . . - p +
// Sem | 1 0 0 1 0 0 1 0 0 1 0 0 1

// if sem == 2
// T0  | . - p +
// T1  | . - p + 
// T2  | . . . . - p +
// T3  | . . . . - p +
// Sem | 2 0 0 2 0 0 2

static void	child_proc(t_ph *ph, t_info *info, int ph_i)
{
	pthread_t	check_die_th;

	if (pthread_create(&check_die_th, NULL, &check_any_ph_die, (void *)(ph)))
		return ;
	pthread_detach(check_die_th);
	while (1)
	{
		if (!philo_take_forks(ph, info, ph_i))
			break ;
		if (!philo_eat(ph, info, ph_i))
			break ;
		if (!philo_sleep(ph, info, ph_i))
			break ;
		if (!philo_think(ph, info, ph_i))
			break ;
		if (info->must_eat_num && info->must_eat_num == ph->eat_num)
		{
			sem_wait(info->must_eat_sem);
			info->must_eat_num_success++;
			sem_post(info->must_eat_sem);
			break ;
		}
	}
	return ;
}

static int	init_sem(t_info *info)
{
	info->forks = sem_open("/forks", O_CREAT, 0666, info->ph_num);
	if (info->forks == SEM_FAILED)
	{
		printf("Error: Failed to open semaphore (forks)\n");
		return (0);
	}
	info->die_sem = sem_open("/die_sem", O_CREAT, 0666, 1);
	if (info->die_sem == SEM_FAILED)
	{
		printf("Error: Failed to open semaphore (die_sem)\n");
		return (0);
	}
	info->must_eat_sem = sem_open("/must_eat_sem", O_CREAT, 0666, 1);
	if (info->must_eat_sem == SEM_FAILED)
	{
		printf("Error: Failed to open semaphore (must_eat_sem)\n");
		return (0);
	}
	return (1);
}

static void	init_philo(t_ph philo[200], t_info *info)
{
	pid_t	pid;
	int		i;

	init_timestamp(info);
	init_sem(info);
	i = -1;
	while (++i < info->ph_num)
	{
		philo[i].ph_i = i;
		philo[i].info = info;
		philo[i].eat_num = 0;
		philo[i].eat_st_time = 0;
		pid = fork();
		if (pid < 0)
		{
			printf("Error: Forking");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
			child_proc(&philo[i], info, i);
	}
	i = -1;
	while (++i < info->ph_num)
		waitpid(pid, NULL, 0);
}

static void	exit_philo(t_info *info)
{
	sem_close(info->forks);
	sem_unlink("/forks");
	sem_close(info->die_sem);
	sem_unlink("/die_sem");
	sem_close(info->must_eat_sem);
	sem_unlink("/must_eat_sem");
}

int	main(int ac, char **av)
{
	t_info	info;
	t_ph	philo[200];

	if (ac < 5 || ac > 6)
		return (printf("Argument Error: ./philo (philo_num) (time to die)\
 (time to eat) (time to sleep) (optional: number of times to eat)"), 1);
	if (!parse_and_check_input(av, &info))
		return (1);
	if (info.ph_num == 1)
	{
		printf("%07lld %d died\n", (long long)0, 1);
		return (0);
	}
	init_philo(philo, &info);
	exit_philo(&info);
}
