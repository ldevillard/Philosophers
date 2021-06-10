/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevilla <ldevilla@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 09:56:42 by ldevilla          #+#    #+#             */
/*   Updated: 2021/06/10 10:44:03 by ldevilla         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->mutex_forks[philo->lfork]);
	display_message(philo, FORK);
	pthread_mutex_lock(&philo->info->mutex_forks[philo->rfork]);
	display_message(philo, FORK);
}

void	clean_forks(t_philo *philo)
{
	display_message(philo, SLEEP);
	pthread_mutex_unlock(&philo->info->mutex_forks[philo->lfork]);
	pthread_mutex_unlock(&philo->info->mutex_forks[philo->rfork]);
	usleep(philo->info->time_to_sleep * 1000);
}
