/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuytters <tuytters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 10:56:58 by tuytters          #+#    #+#             */
/*   Updated: 2021/11/10 12:13:49 by tuytters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	ft_init_env(t_env *env, int argc, char **argv)
{
	env->init_mutex = 0;
	env->die = 0;
	env->nb_philo = ft_atoi(argv[1]);
	env->time_die = ft_atoi(argv[2]);
	env->time_eat = ft_atoi(argv[3]);
	env->time_sleep = ft_atoi(argv[4]);
	env->time_to_go = ft_start();
	if (argc == 6)
		env->eat_max = ft_atoi(argv[5]);
	else
		env->eat_max = 0;
	if (env->nb_philo < 1 || env->time_die < 0 || env->time_eat < 0 ||
		env->time_sleep < 0 || env->eat_max < 0)
		return (1);
	return(0);
}

void	*routine(void *param) 
{
	t_philo			*philo;
	t_env			*env;
	unsigned long	time;
	//unsigned long	time2;
	
	philo = (t_philo *) param;
	env = philo->env;
	//printf("test0\n");
	time = ft_time();
	//time2 = ft_time();
	printf("test1\n");
	// if (env->philo_i[philo->pos].last_eat - ft_time() >= env->time_die)
	// {
	// 	env->die = 1;
	// 	return NULL;
	// }
	printf("%d %d %d\n", philo->rfork, philo->lfork, philo->pos);
	pthread_mutex_lock(&philo->env->fork_i[philo->lfork]);
	printf("test1bis\n");
	printf("%llu %d has taken a fork\n", time - env->time_to_go, philo->pos);
	pthread_mutex_lock(&philo->env->fork_i[philo->rfork]);
	printf("%llu %d has taken a fork\n", time - env->time_to_go, philo->pos);
	printf("%llu %d is eating\n", time - env->time_to_go, philo->pos);
	env->philo_i[philo->pos].last_eat = ft_time();
	philo->max_eat++;
	printf("test2\n");
	while (time < env->philo_i[philo->pos].last_eat + env->time_eat)
		time = ft_time();
	printf("test2bis1\n");
	pthread_mutex_unlock(&philo->env->fork_i[philo->lfork]);
	printf("test2bis2\n");
	pthread_mutex_unlock(&philo->env->fork_i[philo->rfork]);
	printf("test3\n");
	return (NULL);
}

int	ft_init_philo(t_env *env)
{
	int i;

	i = 0;
	env->philo_i = malloc(sizeof(t_philo) * env->nb_philo);
	if (!env->philo_i)
		ft_error("Malloc failed", env);
	while (i < env->nb_philo)
	{
		env->philo_i[i].last_eat = 0;
		env->philo_i[i].pos = i + 1;
		env->philo_i[i].lfork = i;
		env->philo_i[i].rfork = (i + 1) % env->nb_philo;
		env->philo_i[i].env = env;
		env->philo_i[i].max_eat = 0;
		i++;
	}
	return (0);
}

int	ft_init_mutex(t_env *env)
{
	int	i;

	i = 0;
	env->fork_i = malloc(sizeof(pthread_mutex_t) * env->nb_philo);
	if (!env->fork_i)
		ft_error("Malloc failed", env);
	env->init_mutex = 1;
	while (i < env->nb_philo)
	{
		if(pthread_mutex_init(&(env->fork_i[i]), NULL))
			return (1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int			i;
	t_env		*env;

	i = -1;
	env = NULL;
	
	if (argc < 5 || argc > 6)
		ft_error("Error, wrong number of arguments.", env);
	else if (argc == 5)
	{
		
		env = malloc(sizeof(t_env));
		if (!env)
			ft_error("Malloc failed", env);
		ft_init_env(env, argc, argv);
		if (ft_init_philo(env) == 1)
			ft_error("Error, bad init.", env);
		if (argc == 5)
			printf("%d %llu %llu %llu\n", env->nb_philo, env->time_die, env->time_eat, env->time_sleep);
		else if (argc == 6)
			printf("%s %s %s %s %s %d\n", argv[1], argv[2], argv[3], argv[4], argv[5], env->nb_philo);
		while (i++ < env->nb_philo)
		{
			if (pthread_create(&env->philo_i[i].thread_id, NULL, routine, &(env->philo_i[i])))
				return (1);
		}
		i = -1;
		printf("test3bis1\n");
		while (i++ < env->nb_philo)
			pthread_join(env->philo_i[i].thread_id, NULL);
		printf("test3bis2\n");
		all_free(env);
		printf("test4\n");
	}
	return (0);
}
