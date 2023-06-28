/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 08:31:09 by rsoo              #+#    #+#             */
/*   Updated: 2023/06/28 16:00:10 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mod_usleep(int duration, t_ph *ph)
{
	long long	st_time;

	st_time = get_time(ph);
	while (get_time(ph) - st_time < duration)
		usleep(50);
}

void	check_if_dead(t_ph *ph, t_info *info, int i)
{
	pthread_mutex_lock(&info->die_lock);
	printf("	time since last eat:%lld philo: %d\n", get_time(ph) - ph->eat_st_time, i);
	if (get_time(ph) - ph->eat_st_time > info->t_die)
	{
		printf("%07lld %d died\n", get_time(ph), i + 1);
		ph->die_status = 1;
		info->glob_die_status = 1;
	}
	else if (info->glob_die_status)
		ph->die_status = 1;
	pthread_mutex_unlock(&info->die_lock);
}

int	lock_printf(long long time, t_ph *ph, int i, char c)
{
	// pthread_mutex_lock(&ph->info->die_lock);
	printf("	die status: %d, philo: %d\n", ph->die_status, i);
	if (!ph->die_status)
	{
		if (c == 'f')
			printf("%07lld %d has taken a fork\n", time, i + 1);
		else if (c == 'e')
			printf("%07lld %d is eating\n", time, i + 1);
		else if (c == 's')
			printf("%07lld %d is sleeping\n", time, i + 1);
		else if (c == 't')
			printf("%07lld %d is thinking\n", time, i + 1);
		return (1);
	}
	return (0);
	// pthread_mutex_unlock(&ph->info->die_lock);
}

void	init_timestamp(t_info *info)
{
	struct timeval	start;

	gettimeofday(&(start), NULL);
	info->st_time = (long long)start.tv_sec * 1000 + start.tv_usec / 1000;
}

long long	get_time(t_ph *ph)
{
	struct timeval	cur;

	gettimeofday(&cur, NULL);
	return(((long long)cur.tv_sec * 1000 + cur.tv_usec / 1000) - ph->info->st_time);
}
