/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 20:34:59 by rsoo              #+#    #+#             */
/*   Updated: 2023/06/28 15:57:56 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_take_forks(t_ph *ph, t_info *info, int i)
{
	pthread_mutex_lock(&info->fork[i]);
	if (!lock_printf(get_time(ph), ph, i, 'f'))
		return ;

	if (i + 1 == info->ph_num)
		pthread_mutex_lock(&info->fork[0]);
	else
		pthread_mutex_lock(&info->fork[i + 1]);
	if (!lock_printf(get_time(ph), ph, i, 'f'))
		return ;
}

void	philo_eat(t_ph *ph, t_info *info, int i)
{
	ph->eat_st_time = get_time(ph);
	if (!lock_printf(ph->eat_st_time, ph, i, 'e'))
		return ;

	mod_usleep(info->t_eat, ph);
	if (info->must_eat_num)
		ph->eat_num++;

	pthread_mutex_unlock(&info->fork[i]);
	if (i + 1 == info->ph_num)
		pthread_mutex_unlock(&info->fork[0]);
	else
		pthread_mutex_unlock(&info->fork[i + 1]);
}

void	philo_sleep(t_ph *ph, t_info *info, int i)
{
	if (!lock_printf(get_time(ph), ph, i, 's'))
		return ;
	mod_usleep(info->t_sleep, ph);
}

void	philo_think(t_ph *ph, int i)
{
	if (!lock_printf(get_time(ph), ph, i, 't'))
		return ;
}
