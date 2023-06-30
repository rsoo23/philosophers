/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 23:52:01 by rsoo              #+#    #+#             */
/*   Updated: 2023/06/29 23:52:01 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*check_any_ph_die(void *philo)
{
	t_ph	*ph;
	int		i;

	ph = (t_ph *)philo;
	mod_usleep(ph->info->t_eat, ph->info);
	while (!ph->info->glob_die_status)
	{
		sem_wait(ph->info->die_sem);
		i = -1;
		while (++i < ph->info->ph_num)
		{
			if (get_time(ph->info) - ph->eat_st_time > ph->info->t_die)
			{
				ph->info->glob_die_status = 1;
				break ;
			}
		}
		sem_post(ph->info->die_sem);
	}
	sem_wait(ph->info->must_eat_sem);
	if (ph->info->must_eat_num_success != ph->info->ph_num)
		printf("%07lld %d died\n", get_time(ph->info), i + 1);
	sem_post(ph->info->must_eat_sem);
	return (NULL);
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
