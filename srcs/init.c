/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevilla <ldevilla@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 09:56:50 by ldevilla          #+#    #+#             */
/*   Updated: 2021/06/10 10:43:55 by ldevilla         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	init_mutexes(t_info *info)
{
	int	i;

	pthread_mutex_init(&info->mutex_display, NULL);
	pthread_mutex_init(&info->mutex_dead, NULL);
	pthread_mutex_lock(&info->mutex_dead);
	info->mutex_forks = malloc(sizeof(*(info->mutex_forks)) * info->count);
	if (!info->mutex_forks)
		return (1);
	i = 0;
	while (i < info->count)
		pthread_mutex_init(&info->mutex_forks[i++], NULL);
	return (0);
}

static void	init_philos(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->count)
	{
		info->philos[i].is_eating = 0;
		info->philos[i].position = i;
		info->philos[i].lfork = i;
		info->philos[i].rfork = (i + 1) % info->count;
		info->philos[i].eat_count = 0;
		info->philos[i].info = info;
		pthread_mutex_init(&info->philos[i].mutex, NULL);
		pthread_mutex_init(&info->philos[i].mutex_eat, NULL);
		pthread_mutex_lock(&info->philos[i].mutex_eat);
		i++;
	}
}

int	init(t_info *info, int ac, char const **av)
{
	if (convert_arg(av[1], (uint64_t *)&info->count))
		return (1);
	if (convert_arg(av[2], &info->time_to_die))
		return (1);
	if (convert_arg(av[3], &info->time_to_eat))
		return (1);
	if (convert_arg(av[4], &info->time_to_sleep))
		return (1);
	if (ac == 6)
	{
		if (convert_arg(av[5], (uint64_t *)&info->nbr_eat))
			return (1);
	}
	else
		info->nbr_eat = MISSING;
	if (info->count < 2 || info->count > 1000 || info->time_to_die <= 0
		|| info->time_to_eat <= 0 || info->time_to_sleep <= 0
		|| info->nbr_eat < 0)
		return (1);
	info->philos = malloc(sizeof(*(info->philos)) * info->count);
	if (!info->philos)
		return (1);
	init_philos(info);
	return (init_mutexes(info));
}
