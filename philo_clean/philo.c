/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuytters <tuytters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 10:56:58 by tuytters          #+#    #+#             */
/*   Updated: 2021/11/29 11:30:15 by tuytters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	main(int argc, char **argv)
{
	int			i;
	t_env		*env;

	env = NULL;
	if (argc < 5 || argc > 6)
		ft_error("Error, wrong number of arguments.", env);
	else
	{
		env = malloc(sizeof(t_env));
		if (!env)
			ft_error("Malloc failed", env);
		ft_init_env(env, argc, argv);
		if (ft_init_philo(env) == 1)
			ft_error("Error, bad init.", env);
		i = -1;
		while (++i < env->nb_philo)
			if (pthread_create(&env->philo_i[i].thread_id, NULL, routine, &(env->philo_i[i])))
				return (1);
		i = 0;
		while (i < env->nb_philo)
			pthread_join(env->philo_i[i++].thread_id, NULL);
		all_free(env);
	}
	return (0);
}
