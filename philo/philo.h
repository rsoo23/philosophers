/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:40:40 by rsoo              #+#    #+#             */
/*   Updated: 2023/06/12 15:40:40 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <string.h>   // memset
#include <stdio.h>    // printf
#include <stdlib.h>   // malloc, free
#include <unistd.h>   // write, usleep
#include <sys/time.h> // gettimeofday
#include <pthread.h>  // pthread: create, detach, join, mutex_init, mutex_destroy, mutex_lock, mutex_unlock


typedef struct s_info
{
	pthread_mutex_t	fork[200];
	pthread_mutex_t	die_lock;
	int				ph_num;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				must_eat_num;
	int				glob_die_status;
	long long		st_time;
}   t_info;

typedef struct s_ph
{
	pthread_t		th;
	int				ph_i;
	int				eat_num;
	int				die_status;
	long long		time;
	long long		eat_st_time;
	t_info			*info;
}	t_ph;

// main.c

// input_check.c
int			input_check_and_assign(char **av, t_info *info);

// philo_states.c
void		philo_take_forks(t_ph *ph, t_info *info, int i);
void		philo_eat(t_ph *ph, t_info *info, int i);
void		philo_sleep(t_ph *ph, t_info *info, int i);
void		philo_think(t_ph *ph, int i);

// utils_1.c
void		check_if_dead(t_ph *ph, t_info *info, int i);
void		mod_usleep(int duration, t_ph *ph);
int			lock_printf(long long time, t_ph *ph, int i, char c);
void		init_timestamp(t_info *info);
long long	get_time(t_ph *ph);

#endif
