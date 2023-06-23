/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 20:34:59 by rsoo              #+#    #+#             */
/*   Updated: 2023/06/24 00:35:20 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_info *info, int i)
{
	pthread_mutex_lock(&info->fork[i]);
	printf("%07lld %d has taken a fork\n", info->time, i);
	if (i + 1 == info->ph_num)
	{
		pthread_mutex_lock(&info->fork[0]);
		printf("	fork[0]\n");
	}
	else
		pthread_mutex_lock(&info->fork[i + 1]);
	printf("%07lld %d has taken a fork\n", info->time, i);

	get_time(info);
	if (info->time - info->think_st_time <= info->t_die)
		printf("%07lld %d is eating\n", info->time, i);
	else if (info->time - info->think_st_time > info->t_die)
		philo_dies(info, i);

	usleep(info->t_eat * 1000);
	if (info->must_eat_num)
		info->philo[i].eat_num++;

	pthread_mutex_unlock(&info->fork[i]);
	if (i == info->ph_num)
		pthread_mutex_unlock(&info->fork[0]);
	else
		pthread_mutex_unlock(&info->fork[i + 1]);
	// info->philo[i].state = 's';
}

void	philo_sleep(t_info *info, int i)
{
	get_time(info);
	printf("%07lld %d is sleeping\n", info->time, i);
	usleep(info->t_sleep * 1000);
	// info->philo[i].state = 't';
}

void	philo_think(t_info *info, int i)
{
	get_time(info);
	info->think_st_time = info->time;
	printf("%07lld %d is thinking\n", info->time, i);
	// info->philo[i].state = 'e';
}

void	philo_dies(t_info *info, int i)
{
	// get_time(info);
	printf("%07lld %d died\n", info->time, i);
	exit(0);
}
