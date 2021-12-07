/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuytters <tuytters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 10:44:38 by tuytters          #+#    #+#             */
/*   Updated: 2021/12/07 12:29:15 by tuytters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	write_rout(char *txt, t_philo *philo, int pos, int die_or_not)
{
	int	time;

	pthread_mutex_lock(&philo->env->write);
	if (!philo->env->die && philo->env->eat_max)
	{
		time = ft_time() - philo->env->time_to_go;
		printf("%d %d %s\n", time, pos, txt);
	}
	if (!die_or_not)
		pthread_mutex_unlock(&philo->env->write);
}

void	eat_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->env->fork_i[philo->lfork]);
	write_rout("has taken a fork", philo, philo->pos, 0);
	pthread_mutex_lock(&philo->env->fork_i[philo->rfork]);
	write_rout("has taken a fork", philo, philo->pos, 0);
	pthread_mutex_lock(&philo->env->eat);
	philo->last_eat = (ft_time()
			- philo->env->time_to_go);
	write_rout("is eating", philo, philo->pos, 0);
	philo->eat++;
	pthread_mutex_unlock(&philo->env->eat);
	ft_sleep(philo->env->time_eat, philo->env);
	pthread_mutex_unlock(&philo->env->fork_i[philo->rfork]);
	pthread_mutex_unlock(&philo->env->fork_i[philo->lfork]);
}

void	ft_die(t_env *env, t_philo *philo)
{
	int	i;
	int	nbr_philo_eat;

	while (env->eat_max && !env->die)
	{
		nbr_philo_eat = 0;
		i = -1;
		while (++i < env->nb_philo && !env->die)
		{
			pthread_mutex_lock(&philo->env->eat);
			if (((ft_time() - env->time_to_go)
					- philo->env->philo_i[i].last_eat) >= env->time_die)
			{
				write_rout("died", philo, i + 1, 1);
				env->die = 1;
			}
			pthread_mutex_unlock(&philo->env->eat);
		}
		i = -1;
		while (++i < env->nb_philo && !env->die && env->arg6 == 1)
			if (env->philo_i[i].eat >= env->eat_max)
				nbr_philo_eat++;
		if (nbr_philo_eat == env->nb_philo)
			env->eat_max = 0;
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
		write_rout("is thinking", philo, philo->pos, 0);
		ft_sleep(env->time_eat / 2, env);
	}
	while (!env->die && env->eat_max)
	{
		eat_philo(philo);
		if (env->eat_max)
		{
			write_rout("is sleeping", philo, philo->pos, 0);
			ft_sleep(env->time_sleep, env);
			write_rout("is thinking", philo, philo->pos, 0);
		}
	}
	return (NULL);
}
