/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuytters <tuytters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 10:56:58 by tuytters          #+#    #+#             */
/*   Updated: 2021/12/03 09:45:41 by tuytters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	start_thread(t_env *env)
{
	int	i;

	i = -1;
	while (++i < env->nb_philo)
		if (pthread_create(&env->philo_i[i].thread_id,
				NULL, routine, &(env->philo_i[i])))
			return (1);
	if (i == env->nb_philo)
		env->all_philo_create = 1;
	ft_die(env, env->philo_i);
	pthread_mutex_unlock(&env->write);
	i = 0;
	while (i < env->nb_philo)
		pthread_join(env->philo_i[i++].thread_id, NULL);
	return (0);
}

int	all_init(t_env *env, int argc, char **argv)
{
	if (ft_init_env(env, argc, argv))
	{
		ft_error("Error, bad init.", env);
		return (-1);
	}
	if (ft_init_philo(env))
	{
		ft_error("Error, bad init.", env);
		return (-1);
	}
	return (0);
}

int	philo1(t_env *env)
{
	printf("0 1 has taken a fork\n");
	printf("%llu 1 died\n", env->time_die);
	all_free(env);
	return (0);
}

int	main(int argc, char **argv)
{
	t_env		*env;

	env = NULL;
	if (argc < 5 || argc > 6)
	{
		ft_error("Error, wrong number of arguments.", env);
		return (-1);
	}
	else
	{
		env = malloc(sizeof(t_env));
		if (!env)
		{
			ft_error("Malloc failed", env);
			return (-1);
		}
		if (all_init(env, argc, argv) == -1)
			return (-1);
		if (env->nb_philo == 1)
			if (philo1(env) == 0)
				return (0);
		start_thread(env);
		all_free(env);
	}
	return (0);
}
