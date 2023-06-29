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

/*
Notes:
sem_wait(): 
- if s == 0, it no longer can be decremented, the thread will wait on that semaphore 
- if s > 0, it decrements (s--) and executes
sem_post():
- increments the semaphore (s++) once it is done executing

semaphores are basically mutexes with a counter
-: sem_wait()
p: print
+: sem_post()
if sem == 1
T0  | . - p +
T1  | . . . . - p + 
T2  | . . . . . . . - p +
T3  | . . . . . . . . . . - p +
Sem | 1 0 0 1 0 0 1 0 0 1 0 0 1

if sem == 2
T0  | . - p +
T1  | . - p + 
T2  | . . . . - p +
T3  | . . . . - p +
Sem | 2 0 0 2 0 0 2
*/

static void	child_proc()
{

}

static void init_philo_bonus(t_ph philo[200], t_info *info)
{
	sem_t	*forks;
	pid_t	pid;
	int		i;

	init_timestamp(info);
	forks = sem_open("/forks", O_CREAT, 0666, info->ph_num);
	if (fork == SEM_FAILED)
	{
		printf("Error: Failed to open semaphore\n");
		return ;
	}
	i = -1;
	while (++i < info->ph_num)
	{
		pid = fork();
		if (pid < 0)
		{
			printf("Error: Forking");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
			child_proc();
	}
	check_any_ph_die(philo, info);
	i = -1;
	while (++i < info->ph_num)
		wait(NULL);
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
	init_philo_bonus(philo, &info);
}
