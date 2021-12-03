/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuytters <tuytters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 11:14:39 by tuytters          #+#    #+#             */
/*   Updated: 2021/12/03 08:30:42 by tuytters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_init_env(t_env *env, int argc, char **argv)
{
	env->init_mutex = 0;
	env->die = 0;
	env->philo_eat = 0;
	env->arg6 = 0;
	env->all_philo_create = 0;
	env->nb_philo = ft_atoi(argv[1]);
	env->time_die = ft_atoi(argv[2]);
	env->time_eat = ft_atoi(argv[3]);
	env->time_sleep = ft_atoi(argv[4]);
	env->time_to_go = ft_start();
	if (argc == 6)
	{
		env->eat_max = ft_atoi(argv[5]);
		env->arg6 = 1;
	}
	else
		env->eat_max = 1;
	if (env->nb_philo < 1 || env->time_die < 0 || env->time_eat < 0
		|| env->time_sleep < 0 || env->eat_max < 0)
		return (1);
	return (0);
}

int	ft_init_mutex(t_env *env)
{
	int	i;

	i = 0;
	env->fork_i = malloc(sizeof(pthread_mutex_t) * env->nb_philo);
	if (!env->fork_i)
		ft_error("Malloc failed", env);
	env->init_mutex = 1;
	pthread_mutex_init(&(env->write), NULL);
	pthread_mutex_init(&(env->eat), NULL);
	while (i < env->nb_philo)
	{
		if (pthread_mutex_init(&(env->fork_i[i]), NULL))
			return (1);
		i++;
	}
	return (0);
}

int	ft_init_philo(t_env *env)
{
	int	i;

	i = 0;
	env->philo_i = malloc(sizeof(t_philo) * env->nb_philo);
	if (!env->philo_i)
		ft_error("Malloc failed", env);
	while (i < env->nb_philo)
	{
		env->philo_i[i].last_eat = 0;
		env->philo_i[i].pos = i + 1;
		env->philo_i[i].lfork = i;
		env->philo_i[i].rfork = (i + 1) % env->nb_philo;
		env->philo_i[i].env = env;
		i++;
	}
	ft_init_mutex(env);
	return (0);
}
