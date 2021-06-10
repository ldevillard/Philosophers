/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevilla <ldevilla@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 10:43:33 by ldevilla          #+#    #+#             */
/*   Updated: 2021/06/10 10:52:12 by ldevilla         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

# define EAT	0
# define SLEEP	1
# define FORK	2
# define THINK	3
# define DIED	4
# define OVER	5
# define MISSING	0

typedef struct s_philo
{
	int				position;
	int				is_eating;
	uint64_t		limit;
	uint64_t		last_eat;
	int				lfork;
	int				rfork;
	int				eat_count;
	struct s_info	*info;
	pthread_mutex_t	mutex;
	pthread_mutex_t	mutex_eat;
}					t_philo;

typedef struct s_info
{
	int				count;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	int				nbr_eat;
	uint64_t		start;
	t_philo			*philos;
	pthread_mutex_t	*mutex_forks;
	pthread_mutex_t	mutex_display;
	pthread_mutex_t	mutex_dead;
}					t_info;

//PARSING
int			ft_strlen(char *str);
int			ft_atoi(char const *str);
void		ft_putnbr_fd(uint64_t n, int fd);
int			convert_arg(const char *str, uint64_t *be_conv);
uint64_t	get_time(void);
//UTILS
void		free_all(t_info *info);
int			init(t_info *info, int ac, char const **av);
//SIMULATION
void		take_forks(t_philo *philo);
void		clean_forks(t_philo *philo);
void		eat(t_philo *philo);
void		display_message(t_philo *philo, int type);
//THREADS
void		*eat_counter(void *state_v);
void		*check_died(void *philo_v);
void		*routine(void *philo_v);
int			launch_threads(t_info *info);


#endif
