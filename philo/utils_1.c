/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 08:31:09 by rsoo              #+#    #+#             */
/*   Updated: 2023/06/29 10:21:24 by rsoo             ###   ########.fr       */
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

int	lock_printf(long long time, t_ph *ph, int i, char c)
{
	pthread_mutex_lock(&ph->info->die_lock);	
	printf("	gds: %d\n", ph->info->glob_die_status);
	if (!ph->info->glob_die_status)
	{
		if (c == 'f')
			printf("%07lld %d has taken a fork\n", time, i + 1);
		else if (c == 'e')
			printf("%07lld %d is eating\n", time, i + 1);
		else if (c == 's')
			printf("%07lld %d is sleeping\n", time, i + 1);
		else if (c == 't')
			printf("%07lld %d is thinking\n", time, i + 1);
		pthread_mutex_unlock(&ph->info->die_lock);
		return (1);
	}
	else
		printf("%07lld %d died\n", get_time(ph), i + 1);
	pthread_mutex_unlock(&ph->info->die_lock);
	return (0);
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
