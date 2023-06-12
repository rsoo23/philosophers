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
	int			philo_num;
	int			t_die;
	int			t_eat;
	int			t_sleep;
	int			must_eat_num;
	pthread_t   *th;
}   t_info;

// input_check.c
int		input_check_and_assign(char **av, t_info *info);

#endif
