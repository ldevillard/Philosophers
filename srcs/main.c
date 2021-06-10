/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevilla <ldevilla@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 09:56:55 by ldevilla          #+#    #+#             */
/*   Updated: 2021/06/10 11:18:59 by ldevilla         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int ac, char const **av)
{
	t_info	info;

	if (ac != 5 && ac != 6)
	{
		write(2, "Wrong number of arguments\n", 27);
		return (1);
	}
	if (init(&info, ac, av))
	{
		write(2, "Error while parsing\n", 21);
		return (2);
	}
	if (launch_threads(&info))
	{
		free_all(&info);
		write(2, "Error while creating threads\n", 30);
		return (3);
	}
	pthread_mutex_lock(&info.mutex_dead);
	pthread_mutex_unlock(&info.mutex_dead);
	free_all(&info);
	return (0);
}
