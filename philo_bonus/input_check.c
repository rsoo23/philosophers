/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 23:25:58 by rsoo              #+#    #+#             */
/*   Updated: 2023/06/29 23:25:58 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
			if (av[i][j] < '0' || av[i][j] > '9')
				return (0);
	}
	return (1);
}

static int	get_info_1(char **av, t_info *info, long temp)
{
	temp = ft_atoi_long(av[1]);
	if (temp < 1 || temp > 200)
	{
		printf("Error: Philosopher Number (1 - 200)\n");
		return (0);
	}
	info->ph_num = (int)temp;
	temp = ft_atoi_long(av[2]);
	if (temp < 1 || temp > 2147483647)
	{
		printf("Error: Time to die\n");
		return (0);
	}
	info->t_die = (int)temp;
	temp = ft_atoi_long(av[3]);
	if (temp < 1 || temp > 2147483647)
	{
		printf("Error: Time to eat\n");
		return (0);
	}
	info->t_eat = (int)temp;
	return (1);
}

static int	get_info_2(char **av, t_info *info, long temp)
{
	temp = ft_atoi_long(av[4]);
	if (temp < 1 || temp > 2147483647)
	{
		printf("Error: Time to sleep\n");
		return (0);
	}
	info->t_sleep = (int)temp;
	if (av[5])
	{
		temp = ft_atoi_long(av[5]);
		if (temp < 1 || temp > 2147483647)
		{
			printf("Error: Must Eat Number\n");
			return (0);
		}
		info->must_eat_num = (int)temp;
	}
	else
		info->must_eat_num = 0;
	return (1);
}

int	parse_and_check_input(char **av, t_info *info)
{
	long	temp;

	temp = 0;
	if (!check_if_all_digits(av))
	{
		printf("Error: Argument(s) have non-numerical value\n");
		return (0);
	}
	if (!get_info_1(av, info, temp))
		return (0);
	if (!get_info_2(av, info, temp))
		return (0);
	return (1);
}
