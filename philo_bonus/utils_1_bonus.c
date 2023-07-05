/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 23:52:01 by rsoo              #+#    #+#             */
/*   Updated: 2023/06/29 23:52:01 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_sem(t_info *info)
{
	sem_unlink("/forks");
	sem_unlink("/die_sem");
	sem_unlink("/must_eat_sem");
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

void	exit_philo(t_info *info)
{
	sem_close(info->forks);
	sem_close(info->die_sem);
	sem_close(info->must_eat_sem);
	sem_unlink("/forks");
	sem_unlink("/die_sem");
	sem_unlink("/must_eat_sem");
}

void	mod_usleep(int duration, t_info *info)
{
	long long	st_time;

	st_time = get_time(info);
	while (get_time(info) - st_time < duration)
		usleep(50);
}

void	init_timestamp(t_info *info)
{
	struct timeval	start;

	gettimeofday(&(start), NULL);
	info->st_time = (long long)start.tv_sec * 1000 + start.tv_usec / 1000;
}

long long	get_time(t_info *info)
{
	struct timeval	cur;

	gettimeofday(&cur, NULL);
	return ((long long)cur.tv_sec * 1000 + \
	(cur.tv_usec / 1000) - info->st_time);
}
