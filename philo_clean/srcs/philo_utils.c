/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuytters <tuytters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 10:44:38 by tuytters          #+#    #+#             */
/*   Updated: 2021/12/03 08:37:36 by tuytters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	write_rout(char *txt, t_philo *philo, int pos)
{
	int	time;

	time = ft_time() - philo->env->time_to_go;
	pthread_mutex_lock(&philo->env->write);
	if (!philo->env->die)
		printf("%d %d %s\n", time, pos, txt);
	pthread_mutex_unlock(&philo->env->write);
}

void	eat_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->env->fork_i[philo->lfork]);
	write_rout("has taken a fork left", philo, philo->pos);
	pthread_mutex_lock(&philo->env->fork_i[philo->rfork]);
	write_rout("has taken a fork right", philo, philo->pos);
	pthread_mutex_lock(&philo->env->eat);
	philo->env->philo_i[philo->pos - 1].last_eat = (ft_time()
			- philo->env->time_to_go);
	write_rout("is eating", philo, philo->pos);
	philo->env->philo_eat++;
	if (philo->env->philo_eat == philo->env->nb_philo && philo->env->arg6 == 1)
	{
		philo->env->eat_max--;
		philo->env->philo_eat = 0;
	}
	pthread_mutex_unlock(&philo->env->eat);
	ft_sleep(philo->env->time_eat, philo->env);
	pthread_mutex_unlock(&philo->env->fork_i[philo->rfork]);
	pthread_mutex_unlock(&philo->env->fork_i[philo->lfork]);
}

void	ft_die(t_env *env, t_philo *philo)
{
	int	i;

	while (env->eat_max)
	{
		i = -1;
		while (++i < env->nb_philo && !env->die)
		{
			pthread_mutex_lock(&philo->env->eat);
			if (((ft_time() - env->time_to_go)
					- philo->env->philo_i[i].last_eat) >= env->time_die)
			{
				write_rout("died", philo, i + 1);
				pthread_mutex_lock(&philo->env->write);
				env->die = 1;
			}
			pthread_mutex_unlock(&philo->env->eat);
		}
		if (env->die)
			break ;
	}
}

void	*routine(void *param)
{
	t_philo				*philo;
	t_env				*env;

	philo = (t_philo *) param;
	env = philo->env;
	while (!env->all_philo_create)
	{
	}
	if ((philo->pos % 2) != 0)
	{
		write_rout("is thinking", philo, philo->pos);
		ft_sleep(env->time_eat / 2, env);
	}
	while (!env->die && env->eat_max)
	{
		eat_philo(philo);
		if (env->eat_max)
		{
			write_rout("is sleeping", philo, philo->pos);
			ft_sleep(env->time_sleep, env);
			write_rout("is thinking", philo, philo->pos);
		}
	}
	return (NULL);
}
