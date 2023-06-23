/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo _states.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 20:53:50 by rsoo              #+#    #+#             */
/*   Updated: 2023/06/23 10:55:49 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_info *info)
{
	current_timestamp(info);
	pthread_mutex_lock(&info->fork[info->ph_i]);
	printf("%07lld %d has taken a fork\n", info->cur_time, info->ph_i + 1);

	if (info->ph_i == info->ph_num)
		pthread_mutex_lock(&info->fork[0]);
	else
		pthread_mutex_lock(&info->fork[info->ph_i + 1]);
	printf("%07lld %d has taken a fork\n", info->cur_time, info->ph_i + 1);

	printf("%07lld %d is eating\n", info->cur_time, info->ph_i + 1);
	usleep(info->t_eat * 1000);
	if (info->must_eat_num)
		info->philo[info->ph_i].eat_num++;

	pthread_mutex_unlock(&info->fork[info->ph_i]);
	if (info->ph_i == info->ph_num)
		pthread_mutex_unlock(&info->fork[0]);
	else
		pthread_mutex_unlock(&info->fork[info->ph_i + 1]);
	info->philo[info->ph_i].state = 's';
}

void	philo_sleep(t_info *info)
{
	printf("%07lld %d is sleeping\n", info->cur_time, info->ph_i + 1);
	usleep(info->t_sleep * 1000);
	info->philo->state = 't';
}

void	philo_think(t_info *info)
{
	printf("%07lld %d is thinking\n", info->cur_time, info->ph_i + 1);
	info->philo->state = 'e';
}
