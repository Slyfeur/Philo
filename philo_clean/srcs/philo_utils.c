/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuytters <tuytters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 10:44:38 by tuytters          #+#    #+#             */
/*   Updated: 2021/12/01 09:22:19 by tuytters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	write_rout(char *txt, t_philo *philo, int pos)
{
	char	*time;

	time = ft_itoa(ft_time() - philo->env->time_to_go);
	if (!philo->env->die)
		printf("%s %d %s\n", time, pos, txt);
	/* {
		write(1, &time, ft_strlen(time));
		write(1, &philo->pos, ft_digilen(philo->pos));
		write(1, &txt, ft_strlen(time));
		write(1, "\n", 1);
	} */
	free(time);
}

void	eat_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->env->fork_i[philo->lfork]);
	write_rout("has taken a fork", philo, philo->pos);
	pthread_mutex_lock(&philo->env->fork_i[philo->rfork]);
	write_rout("has taken a fork", philo, philo->pos);
	write_rout("is eating", philo, philo->pos);
	philo->env->philo_i[philo->pos].last_eat = (ft_time()
			- philo->env->time_to_go);
	philo->max_eat++;
	ft_sleep(philo->env->time_eat, philo->env);
	pthread_mutex_unlock(&philo->env->fork_i[philo->lfork]);
	pthread_mutex_unlock(&philo->env->fork_i[philo->rfork]);
}

void	*routine(void *param)
{
	t_philo				*philo;
	t_env				*env;

	philo = (t_philo *) param;
	env = philo->env;
	/*time = ft_time() - philo->env->time_to_go;
	if (time - (ft_time() - env->time_to_go) >= env->time_die)
	{
		env->die = 1;
		return NULL;
	}*/
	if (philo->pos % 2 && env->nb_philo > 1)
	{
		write_rout("is thinking", philo, philo->pos);
		ft_sleep(env->time_eat / 50, env);
	}
	while (!env->die /*&& env->eat_max > philo->max_eat*/)
	{
		eat_philo(philo);
		/*if (env->eat_max > philo->max_eat)
		{*/
			write_rout("is sleeping", philo, philo->pos);
			ft_sleep(env->time_sleep, env);
			write_rout("is thinking", philo, philo->pos);
		/*}*/
	}
	return (NULL);
}
