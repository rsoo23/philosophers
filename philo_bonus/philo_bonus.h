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
#include <pthread.h>  
// pthread: create, detach, join, mutex_init,
//  mutex_destroy, mutex_lock, mutex_unlock

#include <fcntl.h>     // O_CREAT
#include <signal.h>    // kill
#include <sys/wait.h>  // waitpid
#include <semaphore.h> // sem_open, sem_close, sem_post, sem_wait, sem_unlink

typedef struct s_info
{
	sem_t			*forks;
	sem_t			*die_sem;
	sem_t			*must_eat_sem;
	int				ph_num;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				must_eat_num;
	int				must_eat_num_success;
	long long		st_time;
}	t_info;

typedef struct s_ph
{
	int				ph_i;
	int				eat_num;
	long long		eat_st_time;
	t_info			*info;
}	t_ph;

// input_check.c
int			parse_and_check_input(char **av, t_info *info);

// philo_states.c
int			philo_take_forks(t_info *info, int i);
int			philo_eat(t_ph *ph, t_info *info, int i);
int			philo_sleep(t_info *info, int i);
int			philo_think(t_info *info, int i);

// utils_1.c
void		mod_usleep(int duration, t_info *info);
void		init_timestamp(t_info *info);
long long	get_time(t_info *info);
int			init_sem(t_info *info);
void		exit_philo(t_info *info);

#endif
