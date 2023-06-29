/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:41:12 by rsoo              #+#    #+#             */
/*   Updated: 2023/06/12 15:41:12 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

#include <string.h>   // memset
#include <stdio.h>    // printf
#include <stdlib.h>   // malloc, free, exit
#include <unistd.h>   // write, usleep, fork
#include <sys/time.h> // gettimeofday
#include <pthread.h>  // pthread: create, detach, join, mutex_init, mutex_destroy, mutex_lock, mutex_unlock

#include <signal.h>    // kill
#include <sys/wait.h>  // waitpid
#include <semaphore.h> // sem_open, sem_close, sem_post, sem_wait, sem_unlink

typedef struct s_info
{
	int				ph_num;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				must_eat_num;
	int				must_eat_num_success;
	int				glob_die_status;
	long long		st_time;
}	t_info;

// input_check.c
int			parse_and_check_input(char **av, t_info *info);

// utils_1.c
void		mod_usleep(int duration, t_info *info);
void		init_timestamp(t_info *info);
long long	get_time(t_info *info);

#endif
