/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
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

	ph->eat_num = 0;
	ph->eat_st_time = 0;
	// if ((ph->ph_i + 1) % 2 == 0)
	// 	usleep(100);
	if (pthread_create(&check_die_th, NULL, &check_any_ph_die, (void *)(ph)))
		return ;
	pthread_detach(check_die_th);
	while (1)
	{
		if (!philo_take_forks(info, ph_i))
			break ;
		if (!philo_eat(ph, info, ph_i))
			break ;
		if (!philo_sleep(info, ph_i))
			break ;
		if (!philo_think(info, ph_i))
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

static void	*check_any_ph_die(void *philo)
{
	t_ph	*ph;

	ph = (t_ph *)philo;
	mod_usleep(ph->info->t_eat, ph->info);
	while (!ph->info->glob_die_status)
	{
		sem_wait(ph->info->die_sem);
		if (get_time(ph->info) - ph->eat_st_time > ph->info->t_die)
		{
			ph->info->glob_die_status = 1;
			break ;
		}
		sem_post(ph->info->die_sem);
	}
	sem_wait(ph->info->must_eat_sem);
	if (ph->info->must_eat_num_success != ph->info->ph_num)
		printf("%07lld %d died\n", get_time(ph->info), i + 1);
	sem_post(ph->info->must_eat_sem);
	return (NULL);
}

static void	wait_any_death(pid_t child_pids[200], t_info *info)
{
	pid_t	term_pid;
	int		i;

	term_pid = waitpid(-1, NULL, 0);
	i = -1;
	if (term_pid > 0)
	{
		while (++i < info->ph_num)
			if (child_pids[i] != term_pid)
				kill(child_pids[i], SIGTERM);
	}
	else if (term_pid < 0)
	{
		printf("Error: terminating pid\n");
		return ;
	}
}

static void	init_philo(t_ph philo[200], t_info *info)
{
	pid_t	pid;
	pid_t	child_pids[200];
	int		i;

	init_timestamp(info);
	init_sem(info);
	info->glob_die_status = 0;
	info->must_eat_num_success = 0;
	i = -1;
	while (++i < info->ph_num)
	{
		philo[i].info = info;
		pid = fork();
		if (pid < 0)
		{
			printf("Error: Forking\n");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
			child_proc(&philo[i], info, i);
		child_pids[i] = pid;
	}
	wait_any_death(child_pids, info);
}

int	main(int ac, char **av)
{
	t_info	info;
	t_ph	philo[200];

	if (ac < 5 || ac > 6)
		return (printf("Argument Error: ./philo (philo_num) (time to die)\
 (time to eat) (time to sleep) (optional: number of times to eat)\n"), 1);
	if (!parse_and_check_input(av, &info))
		return (1);
	if (info.ph_num == 1)
	{
		printf("%07lld %d died\n", (long long)0, 1);
		return (0);
	}
	init_philo(philo, &info);
	sem_close(info.forks);
	sem_close(info.die_sem);
	sem_close(info.must_eat_sem);
	sem_unlink("/forks");
	sem_unlink("/die_sem");
	sem_unlink("/must_eat_sem");
}
