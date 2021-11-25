/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuytters <tuytters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:51:54 by tuytters          #+#    #+#             */
/*   Updated: 2021/11/10 14:42:41 by tuytters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	main(int argc, char **argv)
{
	t_env	*env;
	int		i;

	i = -1;
	env = NULL;
	if (argc < 5 || argc > 6)
		ft_error("Error, wrong number of arguments.", env);
	else
	{
		env = malloc(sizeof(t_env));
		if (!env)
			ft_error("Malloc failed", env);
		ft_init_env(env, argc, argv);
		if (ft_init_philo(env) != 0)
			ft_error("Error, bad init.", env);
		while (i++ < env->nb_philo)
		{
			if(pthread_create(&env->philo_i[i].thread_id, NULL, routine, &(env->philo_i[i])))
				return (1);
		}
		i = -1;
		while (i++ < env->nb_philo)
			pthread_join(env->philo_i[i].thread_id, NULL);
		all_free(env);
	}
	return (0);
}