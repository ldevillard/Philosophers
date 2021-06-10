/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevilla <ldevilla@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 10:49:26 by ldevilla          #+#    #+#             */
/*   Updated: 2021/06/10 11:18:50 by ldevilla         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*eat_counter(void *arg)
{
	t_info	*info;
	int		i;
	int		total;

	info = (t_info *)arg;
	total = 0;
	while (total < info->nbr_eat)
	{
		i = 0;
		while (i < info->count)
			pthread_mutex_lock(&info->philos[i++].mutex_eat);
		total++;
	}
	display_message(&info->philos[0], OVER);
	pthread_mutex_unlock(&info->mutex_dead);
	return ((void *)0);
}

void	*check_died(void *philo_v)
{
	t_philo	*philo;

	philo = (t_philo *)philo_v;
	while (1)
	{
		pthread_mutex_lock(&philo->mutex);
		if (!philo->is_eating && get_time() > philo->limit)
		{
			display_message(philo, DIED);
			pthread_mutex_unlock(&philo->mutex);
			pthread_mutex_unlock(&philo->info->mutex_dead);
			return ((void *)0);
		}
		pthread_mutex_unlock(&philo->mutex);
		usleep(1000);
	}
}

void	*routine(void *philo_v)
{
	t_philo		*philo;
	pthread_t	tid;

	philo = (t_philo *)philo_v;
	philo->last_eat = get_time();
	philo->limit = philo->last_eat + philo->info->time_to_die;
	if (pthread_create(&tid, NULL, &check_died, philo_v) != 0)
		return ((void *)1);
	pthread_detach(tid);
	while (1)
	{
		take_forks(philo);
		eat(philo);
		reset_forks(philo);
		display_message(philo, THINK);
	}
	return ((void *)0);
}

int	launch_threads(t_info *info)
{
	int			i;
	pthread_t	th;
	void		*philo;

	info->start = get_time();
	if (info->nbr_eat > 0)
	{
		if (pthread_create(&th, NULL, &eat_counter, (void *)info) != 0)
			return (1);
		pthread_detach(th);
	}
	i = 0;
	while (i < info->count)
	{
		philo = (void *)(&info->philos[i]);
		if (pthread_create(&th, NULL, &routine, philo) != 0)
			return (1);
		pthread_detach(th);
		usleep(100);
		i++;
	}
	return (0);
}
