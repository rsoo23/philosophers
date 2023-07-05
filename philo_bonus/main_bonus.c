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

static void	*check_any_ph_die(void *philo)
{
	t_ph	*ph;

	ph = (t_ph *)philo;
	mod_usleep(ph->info->t_eat, ph->info);
	while (1)
	{
		sem_wait(ph->die_sem);
		if (get_time(ph->info) - ph->eat_st_time > ph->info->t_die)
			break ;
		sem_post(ph->die_sem);
	}
	printf("%07lld %d died\n", get_time(ph->info), ph->ph_i + 1);
	exit(DIED);
}

static void	child_proc(t_ph *ph, int ph_i)
{
	pthread_t	check_die_th;

	sem_unlink("/die_sem");
	ph->die_sem = sem_open("/die_sem", O_CREAT, 0666, 1);
	ph->eat_num = 0;
	ph->eat_st_time = 0;
	ph->ph_i = ph_i;
	if (pthread_create(&check_die_th, NULL, &check_any_ph_die, (void *)(ph)))
		return ;
	pthread_detach(check_die_th);
	while (1)
	{
		philo_take_forks(ph, ph_i);
		philo_eat(ph, ph_i);
		if (ph->info->must_eat_num && ph->info->must_eat_num == ph->eat_num)
			break ;
		philo_sleep(ph, ph_i);
		philo_think(ph, ph_i);
	}
	sem_close(ph->die_sem);
	sem_unlink("/die_sem");
	exit(MUST_EAT_DONE);
}

static void	wait_for_child_proc(pid_t child_pids[200], t_info *info)
{
	pid_t	term_pid;
	int		i;
	int		status;
	int		must_eat_success;

	must_eat_success = 0;
	while (must_eat_success < info->ph_num)
	{
		// write(1, "wait\n", 5);
		// printf("%d\n", must_eat_success);
		term_pid = waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == DIED)
		{
			i = -1;
			while (++i < info->ph_num)
				if (child_pids[i] != term_pid)
					kill(child_pids[i], SIGTERM);
			return ;
		}
		else if (WEXITSTATUS(status) == MUST_EAT_DONE)
			must_eat_success++;
		// printf("	%d\n", must_eat_success);
	}
}

static void	init_philo(t_ph philo[200], t_info *info)
{
	pid_t	pid;
	pid_t	child_pids[200];
	int		i;

	init_timestamp(info);
	sem_unlink("/forks");
	info->forks = sem_open("/forks", O_CREAT, 0666, info->ph_num);
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
			child_proc(&philo[i], i);
		child_pids[i] = pid;
	}
	wait_for_child_proc(child_pids, info);
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
	sem_unlink("/forks");
}
