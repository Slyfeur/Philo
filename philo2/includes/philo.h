/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuytters <tuytters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 11:27:21 by tuytters          #+#    #+#             */
/*   Updated: 2021/11/10 14:34:06 by tuytters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>

struct	s_env;

typedef struct s_philo
{
	int					pos;
	int					lfork;
	int					rfork;
	int					max_eat;
	unsigned long long	last_eat;
	struct s_env		*env;
	pthread_t			thread_id;
}	t_philo;

typedef struct s_env
{
	int					nb_philo;
	unsigned long long	time_die;
	unsigned long long	time_eat;
	unsigned long long	time_sleep;
	int					eat_max;
	int					die;
	int					init_mutex;
	unsigned long long	time_to_go;
	t_philo				*philo_i;
	pthread_mutex_t		*fork_i;
}	t_env;

void			all_free(t_env *env);
int				ft_error(char *str, t_env *env);
long long		ft_atoi(const char *nptr);
unsigned long	ft_time(void);
unsigned long	ft_start(void);

//init.c
int	ft_init_env(t_env *env, int argc, char **argv);
int	ft_init_philo(t_env *env);
int	ft_init_mutex(t_env *env);

//ft_philo.c
void	*routine(void *param);

#endif