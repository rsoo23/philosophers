/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 10:49:17 by rsoo              #+#    #+#             */
/*   Updated: 2023/07/12 11:33:57 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static char	*ft_strjoin_char(char const *s1, char c)
{
	char			*res;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	if (!s1)
		return (0);
	res = malloc(ft_strlen(s1) + 2);
	if (!res)
		return (0);
	while (s1[i])
		res[j++] = s1[i++];
	i = 0;
	res[j++] = c;
	res[j] = '\0';
	return (res);
}

void	init_loc_die_sem(t_ph *ph)
{
	ph->loc_die_sem_name = ft_strjoin_char("/loc_die_sem", ph->ph_i + 48);
	sem_unlink(ph->loc_die_sem_name);
	ph->loc_die_sem = sem_open(ph->loc_die_sem_name, O_CREAT, 0666, 1);
}

void	close_loc_die_sem(t_ph *ph)
{
	sem_close(ph->loc_die_sem);
	sem_unlink(ph->loc_die_sem_name);
}
