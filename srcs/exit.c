/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevilla <ldevilla@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 09:56:34 by ldevilla          #+#    #+#             */
/*   Updated: 2021/06/10 10:43:49 by ldevilla         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	free_all(t_info *info)
{
	int	i;

	if (info->mutex_forks)
	{
		i = 0;
		while (i < info->count)
			pthread_mutex_destroy(&info->mutex_forks[i++]);
		free(info->mutex_forks);
	}
	if (info->philos)
	{
		i = 0;
		while (i < info->count)
		{
			pthread_mutex_destroy(&info->philos[i].mutex);
			pthread_mutex_destroy(&info->philos[i++].mutex_eat);
		}
		free(info->philos);
	}
	pthread_mutex_destroy(&info->mutex_display);
	pthread_mutex_destroy(&info->mutex_dead);
}
