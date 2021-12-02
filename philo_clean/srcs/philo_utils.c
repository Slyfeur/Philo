/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuytters <tuytters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 10:44:38 by tuytters          #+#    #+#             */
/*   Updated: 2021/12/02 12:07:38 by tuytters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	write_rout(char *txt, t_philo *philo, int pos)
{
	int	time;

	time = ft_time() - philo->env->time_to_go;
	pthread_mutex_lock(&philo->env->write);
	if (!philo->env->die /*&& philo->env->eat_max*/)
		printf("%d %d %s\n", time, pos, txt);
	pthread_mutex_unlock(&philo->env->write);
	/* {
		write(1, &time, ft_strlen(time));
		write(1, &philo->pos, ft_digilen(philo->pos));
		write(1, &txt, ft_strlen(time));
		write(1, "\n", 1);
	} */
}

void	eat_philo(t_philo *philo)
{
	//printf("test1\n");
	if (!(philo->env->philo_i[philo->pos].last_eat < philo->env->philo_i[(philo->pos - 1) % philo->env->nb_philo].last_eat || philo->env->philo_i[philo->pos].last_eat < philo->env->philo_i[(philo->pos + 1) % philo->env->nb_philo].last_eat))
	{
		ft_sleep(100, philo->env);
	}
	if (&philo->env->fork_i[philo->lfork] < &philo->env->fork_i[philo->rfork])
	{
		pthread_mutex_lock(&philo->env->fork_i[philo->lfork]);
		//printf("test1ok\n");
		write_rout("has taken a fork left", philo, philo->pos);
		//printf("test2\n");
		pthread_mutex_lock(&philo->env->fork_i[philo->rfork]);
		//printf("test2ok\n");
		write_rout("has taken a fork right", philo, philo->pos);
	}
	else
	{
		pthread_mutex_lock(&philo->env->fork_i[philo->rfork]);
		//printf("test2ok\n");
		write_rout("has taken a fork right", philo, philo->pos);
		pthread_mutex_lock(&philo->env->fork_i[philo->lfork]);
		//printf("test1ok\n");
		write_rout("has taken a fork left", philo, philo->pos);
	}
	//pthread_mutex_lock(&philo->env->eat);
	philo->env->philo_i[philo->pos].last_eat = (ft_time()
			- philo->env->time_to_go);
	write_rout("is eating", philo, philo->pos);
	philo->env->philo_eat++;
	if (philo->env->philo_eat == philo->env->nb_philo && philo->env->arg6 == 1)
	{
		philo->env->eat_max--;
		philo->env->philo_eat = 0;
	}
	
	//pthread_mutex_unlock(&philo->env->eat);
	ft_sleep(philo->env->time_eat, philo->env);
	pthread_mutex_unlock(&philo->env->fork_i[philo->lfork]);
	pthread_mutex_unlock(&philo->env->fork_i[philo->rfork]);
}

//void	max_eat_die(t_env *env, t_philo *philo)


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
	if (philo->pos % 2 && env->nb_philo >= 1)
	{
		write_rout("is thinking", philo, philo->pos);
		ft_sleep(env->time_eat, env);
	}
	while (!env->die && env->eat_max)
	{
		// if (((ft_time() - env->time_to_go) - philo->env->philo_i[philo->pos].last_eat) >= env->time_die)
		// {
		// 	env->die = philo->pos;
		// 	pthread_mutex_lock(&philo->env->write);
		// 	//env->time_eat = env-> time_die - (ft_time() - env->time_to_go) - philo->env->philo_i[philo->pos].last_eat;
		// }
		eat_philo(philo);
		if (env->eat_max)
		{
			write_rout("is sleeping", philo, philo->pos);
			ft_sleep(env->time_sleep, env);
			write_rout("is thinking", philo, philo->pos);
		}
		// else
		// {
		// 	pthread_mutex_lock(&philo->env->write);
		// }
		//printf("philo %d die = %d %llu %llu \n", philo->pos, env->die, (ft_time() - env->time_to_go), philo->env->philo_i[philo->pos].last_eat);
		
	}
	return (NULL);
}
