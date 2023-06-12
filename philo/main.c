/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:55:54 by rsoo              #+#    #+#             */
/*   Updated: 2023/06/12 15:55:54 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	mutex;

void	*routine(void *arg)
{
	int i = 0;
	int	*res = malloc(sizeof(int));

	while (i < 1000000)
	{
		pthread_mutex_lock(&mutex);
		i++;
		pthread_mutex_unlock(&mutex);
	}
	*res = i;
	return ((void *)res);
}

// gcc -Wall -Wextra -Werror -pthread main.c

/*
pthread_join:
- when thread is created, it is split into the: new thread and main thread
- pthread_join causes the main thread to wait until the new thread is complete
pthread_join: like a wait function for threads

pthread_mutex_lock + unlock (mutual exclusive):
- when a thread has this, it makes sure that no other thread is going to execute
- preventing race conditions
*/

int main(int ac, char **av)
{
	t_info	info;
	int		i;
	int		*res

	i = -1;
	if (ac < 5 || ac > 6 || !input_check_and_assign(av, &info))
		return (1);
	pthread_mutex_init(&mutex, NULL);
	info.th = malloc(info.philo_num * sizeof(pthread_t));
	if (!info.th)
		return (1);
	while (++i < info.philo_num)
		if (pthread_create(&info.th[i], NULL, &routine, NULL))
			return (1);
	i = -1;
	while (++i < info.philo_num)
		if (pthread_join(info.th[i], (void **)&res))
			return (1);
	printf("result: %d", i);
	pthread_mutex_destroy(&mutex);
}
