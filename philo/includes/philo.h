/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuytters <tuytters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 11:27:21 by tuytters          #+#    #+#             */
/*   Updated: 2021/12/06 15:14:42 by tuytters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>

typedef struct s_philo
{
	int					pos;
	int					lfork;
	int					rfork;
	unsigned long long	last_eat;
	int					eat;
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
	int					philo_eat;
	int					arg6;
	int					all_philo_create;
	unsigned long long	time_to_go;
	t_philo				*philo_i;
	pthread_mutex_t		*fork_i;
	pthread_mutex_t		write;
	pthread_mutex_t		eat;
}	t_env;

/* FREE */

void			all_free(t_env *env);

/* ERROR */

int				ft_error(char *str, t_env *env);

/* CONVERT */

int				ft_isdigit(int c);
long long		ft_atoi(const char *nptr);

/* UTILS */

int				check_digit(char **argv);
unsigned long	ft_time(void);
unsigned long	ft_start(void);
void			ft_sleep(unsigned long long time, t_env *env);

/* PHILO_UTILS */

void			eat_philo(t_philo *philo);
void			ft_die(t_env *env, t_philo *philo);
void			*routine(void *param);

/* INIT */

int				ft_init_philo(t_env *env);
int				ft_init_mutex(t_env *env);
int				ft_init_env(t_env *env, int argc, char **argv);

#endif