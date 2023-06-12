/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 21:37:15 by rsoo              #+#    #+#             */
/*   Updated: 2023/06/12 21:37:15 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int free_and_exit(char *error, int return_val, t_info *info)
{
    if (info)
        free(info);
    printf("Error: %s\n", error);
    return (return_val);
}
