/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:06:42 by rsoo              #+#    #+#             */
/*   Updated: 2023/06/12 18:06:42 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int ft_isdigit(int c)
{
    if (c >= '0' && c <= '9')
        return (1);
    return (0);
}

static long	ft_atoi_long(const char *str)
{
	int		i;
	long	sign;
	long	number;

	i = 0;
	sign = 1;
	number = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = (number * 10) + (str[i] - 48);
		i++;
	}
	return (sign * number);
}

static int	check_if_all_digits(char **av)
{
	int	i;
	int	j;

	i = 0;
	while (av[++i])
	{
		j = -1;
		while (av[i][++j])
			if (!ft_isdigit(av[i][j]))
				return (0);
	}
	return (1);
}

static int	check_num_size(char **av)
{
	int		i;
	long	num;

	i = -1;
	num = 0;
	while (av[++i])
	{
		num = ft_atoi_long(av[i]);
		if (num > 2147483647 || num < -2147483648)
			return (0);
	}
	return (1);
}

int	input_check_and_assign(char **av, t_info *info)
{
	if (!check_if_all_digits(av))
		return (0);
	if (!check_num_size(av))
		return (0);
	info->ph_num = (int)ft_atoi_long(av[1]);
	info->t_die = (int)ft_atoi_long(av[2]);
	info->t_eat = (int)ft_atoi_long(av[3]);
	info->t_sleep = (int)ft_atoi_long(av[4]);
	if (av[5])
		info->must_eat_num = (int)ft_atoi_long(av[5]);
	// printf("%d, %d, %d, %d\n", info->ph_num, info->t_die, info->t_eat, info->t_sleep);
	return (1);
}
