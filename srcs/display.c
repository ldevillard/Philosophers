/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevilla <ldevilla@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 09:56:20 by ldevilla          #+#    #+#             */
/*   Updated: 2021/06/10 11:35:51 by ldevilla         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static char	*get_message(int type)
{
	if (type == EAT)
		return (" is eating\n");
	else if (type == SLEEP)
		return (" is sleeping\n");
	else if (type == FORK)
		return (" has taken a fork\n");
	else if (type == THINK)
		return (" is thinking\n");
	else if (type == OVER)
		return ("end of simulation\n");
	return (" died\n");
}

void	display_message(t_philo *philo, int type)
{
	static bool	died = false;

	pthread_mutex_lock(&philo->info->mutex_display);
	if (!died)
	{
		if (type == OVER)
			died = true;
		write(1, "[", 1);
		ft_putnbr_fd(get_time() - philo->info->start, 1);
		write(1, "]", 1);
		write(1, " - ", 3);
		if (type != OVER)
			ft_putnbr_fd(philo->position + 1, 1);
		if (type >= DIED)
			died = true;
		write(1, get_message(type), ft_strlen(get_message(type)));
	}
	pthread_mutex_unlock(&philo->info->mutex_display);
}
