/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuytters <tuytters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 08:51:24 by tuytters          #+#    #+#             */
/*   Updated: 2021/11/10 14:33:34 by tuytters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo_eat(t_philo *philo, t_env *env)
{
	unsigned long time;
	// (void) philo;
	// (void) env;

	time = ft_time();
	//pthread_mutex_lock(&philo->env->fork_i[philo->lfork]);
	printf("test1\n");
	//printf("%llu %d has taken a fork\n", time - env->time_to_go, philo->pos);
	//pthread_mutex_lock(&philo->env->fork_i[philo->rfork]);
	printf("%llu %d has taken a fork\n", time - env->time_to_go, philo->pos);
	//printf("%llu %d is eating\n", time - env->time_to_go, philo->pos);
	printf("test2\n");
	env->philo_i[philo->pos].last_eat = ft_time();
	philo->max_eat++;
	// while (time < env->philo_i[philo->pos].last_eat + env->time_eat)
	// 	time = ft_time();
	//pthread_mutex_unlock(&philo->env->fork_i[philo->lfork]);
	//pthread_mutex_unlock(&philo->env->fork_i[philo->rfork]);
}
void	*routine(void *param)
{
	t_philo	*philo;
	t_env	*env;

	philo = (t_philo *) param;
	env = philo->env;
	printf("test\n");
	philo_eat(philo, env);
	return (NULL);
}
