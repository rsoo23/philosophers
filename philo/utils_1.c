/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 08:31:09 by rsoo              #+#    #+#             */
/*   Updated: 2023/06/29 14:57:23 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
