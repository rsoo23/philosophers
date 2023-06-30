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

void	check_any_ph_die(t_ph philo[200], t_info *info)
{
	int	i;

	mod_usleep(info->t_eat, info);
	while (!info->glob_die_status)
	{
		sem_wait(info->die_sem);
		i = -1;
		while (++i < info->ph_num)
		{
			if (get_time(info) - philo[i].eat_st_time > info->t_die)
			{
				info->glob_die_status = 1;
				break ;
			}
		}
		sem_post(info->die_sem);
	}
	sem_wait(info->must_eat_sem);
	if (info->must_eat_num_success != info->ph_num)
		printf("%07lld %d died\n", get_time(info), i + 1);
	sem_post(info->must_eat_sem);
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
