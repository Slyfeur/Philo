/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuytters <tuytters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 10:44:38 by tuytters          #+#    #+#             */
/*   Updated: 2021/11/29 12:55:00 by tuytters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	eat_philo(t_philo *philo)
{
	unsigned long long time;
	pthread_mutex_lock(&philo->env->fork_i[philo->lfork]);	
	time = (ft_time() - philo->env->time_to_go);
	printf("%llu %d has taken a fork\n", time, philo->pos);
	pthread_mutex_lock(&philo->env->fork_i[philo->rfork]);
	printf("%llu %d has taken a fork\n", time, philo->pos);
	printf("%llu %d is eating\n", time, philo->pos);
	philo->env->philo_i[philo->pos].last_eat = (ft_time() - philo->env->time_to_go);
	philo->max_eat++;
	ft_sleep(philo->env->time_eat, philo->env);
	pthread_mutex_unlock(&philo->env->fork_i[philo->lfork]);
	pthread_mutex_unlock(&philo->env->fork_i[philo->rfork]);
}

void	*routine(void *param)
{
	t_philo				*philo;
	t_env				*env;
	unsigned long long	time;

	philo = (t_philo *) param;
	env = philo->env;
	// time = ft_time() - philo->env->time_to_go;
	// if (time - (ft_time() - env->time_to_go) >= env->time_die)
	// {
	// 	env->die = 1;
	// 	return NULL;
	// }
	if (philo->pos % 2 && env->nb_philo > 1)
	{
		time = ft_time() - philo->env->time_to_go;
		printf("%llu %d is thinking\n", time, philo->pos);
		ft_sleep(env->time_eat / 50, env);
	}
	while(!env->die && env->eat_max > philo->max_eat)
	{
		eat_philo(philo);
		time = ft_time() - philo->env->time_to_go;
		if (env->eat_max > philo->max_eat)
		{
			printf("%llu %d is sleeping\n", time, philo->pos);
			ft_sleep(env->time_sleep, env);
			time = ft_time() - philo->env->time_to_go;
			printf("%llu %d is thinking\n", time, philo->pos);
		}
	}
	return (NULL);
}
