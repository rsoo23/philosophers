/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 20:34:59 by rsoo              #+#    #+#             */
/*   Updated: 2023/06/26 15:34:03 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	mod_usleep(int duration, t_ph *ph)
{
	long long	st_time;

	st_time = get_time(ph);
	while (get_time(ph) - st_time < duration)
		usleep(duration / 20);
}

int	check_if_dead(t_ph *ph, t_info *info, int i)
{
	// printf("	time_now: %lld, eat_st_time: %lld\n", get_time(ph), ph->eat_st_time);
	if (get_time(ph) - ph->eat_st_time > info->t_die)
	{
		philo_dies(ph, info, i);
		return (1);
	}
	return (0);
}

/*
Process:
1. gets first fork
2. gets second fork
3. eat
4. eat + delay with mod_usleep
5. unlocks first forks
6. unlocks second fork
*/
void	philo_eat(t_ph *ph, t_info *info, int i)
{
	pthread_mutex_lock(&info->fork[i]);
	ph->time = get_time(ph);
	printf("%07lld %d has taken a fork\n", ph->time, i + 1);

	if (i + 1 == info->ph_num)
		pthread_mutex_lock(&info->fork[0]);
	else
		pthread_mutex_lock(&info->fork[i + 1]);
	printf("%07lld %d has taken a fork\n", ph->time, i + 1);

	if (check_if_dead(ph, ph->info, ph->ph_i))
		return ;
	ph->time = get_time(ph);
	printf("%07lld %d is eating\n", ph->time, i + 1);
	ph->eat_st_time = ph->time;

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
	printf("%07lld %d is sleeping\n", get_time(ph), i + 1);
	mod_usleep(info->t_sleep, ph);
}

void	philo_think(t_ph *ph, int i)
{
	printf("%07lld %d is thinking\n", get_time(ph), i + 1);
}

void	philo_dies(t_ph *ph, t_info *info, int i)
{
	pthread_mutex_unlock(&info->fork[i]);
	if (i + 1 == info->ph_num)
		pthread_mutex_unlock(&info->fork[0]);
	else
		pthread_mutex_unlock(&info->fork[i + 1]);
	printf("%07lld %d died\n", ph->time, i + 1);
	ph->die_status = 1;
}
