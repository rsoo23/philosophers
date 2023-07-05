/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 20:34:59 by rsoo              #+#    #+#             */
/*   Updated: 2023/07/05 20:55:48 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	lock_printf(long long time, t_ph *ph, int i, char c)
{
	pthread_mutex_lock(&ph->info->die_lock);
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
	pthread_mutex_unlock(&ph->info->die_lock);
	return (0);
}

int	philo_take_forks(t_ph *ph, t_info *info, int i)
{
	pthread_mutex_lock(&info->fork[i]);
	if (!lock_printf(get_time(info), ph, i, 'f'))
		return (0);
	pthread_mutex_lock(&info->fork[(i + 1) % info->ph_num]);
	if (!lock_printf(get_time(info), ph, i, 'f'))
		return (0);
	return (1);
}

int	philo_eat(t_ph *ph, t_info *info, int i)
{
	pthread_mutex_lock(&info->die_lock);
	ph->eat_st_time = get_time(info);
	pthread_mutex_unlock(&info->die_lock);
	if (!lock_printf(ph->eat_st_time, ph, i, 'e'))
		return (0);
	mod_usleep(info->t_eat, info);
	if (info->must_eat_num)
		ph->eat_num++;
	pthread_mutex_unlock(&info->fork[i]);
	pthread_mutex_unlock(&info->fork[(i + 1) % info->ph_num]);
	return (1);
}

int	philo_sleep(t_ph *ph, t_info *info, int i)
{
	if (!lock_printf(get_time(info), ph, i, 's'))
		return (0);
	mod_usleep(info->t_sleep, info);
	return (1);
}

int	philo_think(t_ph *ph, t_info *info, int i)
{
	if (!lock_printf(get_time(info), ph, i, 't'))
		return (0);
	return (1);
}
