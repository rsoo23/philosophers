/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_states_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 08:55:21 by rsoo              #+#    #+#             */
/*   Updated: 2023/07/05 10:32:19 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	lock_printf(long long time, t_info *info, int i, char c)
{
	sem_wait(info->die_sem);
	if (c == 'f')
		printf("%07lld %d has taken a fork\n", time, i + 1);
	else if (c == 'e')
		printf("%07lld %d is eating\n", time, i + 1);
	else if (c == 's')
		printf("%07lld %d is sleeping\n", time, i + 1);
	else if (c == 't')
		printf("%07lld %d is thinking\n", time, i + 1);
	sem_post(info->die_sem);
	return (1);
}

int	philo_take_forks(t_info *info, int i)
{
	sem_wait(info->forks);
	if (!lock_printf(get_time(info), info, i, 'f'))
	{
		sem_post(info->forks);
		return (0);
	}
	sem_wait(info->forks);
	if (!lock_printf(get_time(info), info, i, 'f'))
	{
		sem_post(info->forks);
		sem_post(info->forks);
		return (0);
	}
	return (1);
}

int	philo_eat(t_ph *ph, t_info *info, int i)
{
	sem_wait(info->die_sem);
	ph->eat_st_time = get_time(info);
	sem_post(info->die_sem);
	if (!lock_printf(ph->eat_st_time, info, i, 'e'))
		return (0);
	mod_usleep(info->t_eat, info);
	if (info->must_eat_num)
		ph->eat_num++;
	sem_post(info->forks);
	sem_post(info->forks);
	return (1);
}

int	philo_sleep(t_info *info, int i)
{
	if (!lock_printf(get_time(info), info, i, 's'))
		return (0);
	mod_usleep(info->t_sleep, info);
	return (1);
}

int	philo_think(t_info *info, int i)
{
	if (!lock_printf(get_time(info), info, i, 't'))
		return (0);
	return (1);
}
