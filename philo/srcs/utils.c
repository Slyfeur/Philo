/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuytters <tuytters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 10:08:08 by tuytters          #+#    #+#             */
/*   Updated: 2021/12/03 13:47:33 by tuytters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_digit(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
		{
			if (ft_isdigit(argv[i][j]) == 0)
				return (1);
		}
	}
	return (0);
}

unsigned long	ft_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * (unsigned long) 1000) + (time.tv_usec / 1000));
}

unsigned long	ft_start(void)
{
	usleep(700000);
	return (ft_time());
}

void	ft_sleep(unsigned long long time, t_env *env)
{
	unsigned long long	start;

	start = ft_time();
	while (!env->die)
	{
		if (ft_time() - start >= time)
			break ;
		usleep(env->nb_philo);
	}
}
