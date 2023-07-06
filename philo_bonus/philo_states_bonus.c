/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_states_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 08:55:21 by rsoo              #+#    #+#             */
/*   Updated: 2023/07/06 09:10:33 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	lock_printf(long long time, t_ph *ph, int i, char c)
{
	sem_wait(ph->loc_die_sem);
	if (c == 'f')
		printf("%07lld %d has taken a fork\n", time, i + 1);
	else if (c == 'e')
		printf("%07lld %d is eating\n", time, i + 1);
	else if (c == 's')
		printf("%07lld %d is sleeping\n", time, i + 1);
	else if (c == 't')
		printf("%07lld %d is thinking\n", time, i + 1);
	sem_post(ph->loc_die_sem);
}

void	philo_take_forks(t_ph *ph, int i)
{
	sem_wait(ph->info->forks);
	lock_printf(get_time(ph->info), ph, i, 'f');
	sem_wait(ph->info->forks);
	lock_printf(get_time(ph->info), ph, i, 'f');
}

void	philo_eat(t_ph *ph, int i)
{
	sem_wait(ph->loc_die_sem);
	ph->eat_st_time = get_time(ph->info);
	sem_post(ph->loc_die_sem);
	lock_printf(ph->eat_st_time, ph, i, 'e');
	mod_usleep(ph->info->t_eat, ph->info);
	if (ph->info->must_eat_num)
		ph->eat_num++;
	sem_post(ph->info->forks);
	sem_post(ph->info->forks);
}

void	philo_sleep(t_ph *ph, int i)
{
	lock_printf(get_time(ph->info), ph, i, 's');
	mod_usleep(ph->info->t_sleep, ph->info);
}

void	philo_think(t_ph *ph, int i)
{
	lock_printf(get_time(ph->info), ph, i, 't');
}
