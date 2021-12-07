/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuytters <tuytters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:00:58 by tuytters          #+#    #+#             */
/*   Updated: 2021/12/03 13:43:24 by tuytters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	all_free(t_env *env)
{
	int	i;

	i = 0;
	if (env->init_mutex == 1)
	{
		while (i < env->nb_philo)
			pthread_mutex_destroy(&env->fork_i[i++]);
		pthread_mutex_destroy(&env->write);
		pthread_mutex_destroy(&env->eat);
	}
	if (env->philo_i)
		free(env->philo_i);
	if (env->fork_i)
		free(env->fork_i);
	if (env)
		free(env);
}
