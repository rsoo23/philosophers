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
	int				ph_num;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				must_eat_num;
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
long long	get_time(t_ph *ph);

// input_check.c
int			input_check_and_assign(char **av, t_info *info);

// philo_states.c
int			check_if_dead(t_ph *ph, t_info *info, int i);
void		philo_eat(t_ph *ph, t_info *info, int i);
void		philo_sleep(t_ph *ph, t_info *info, int i);
void		philo_think(t_ph *ph, int i);
void		philo_dies(t_ph *ph, t_info *info, int i);

#endif
