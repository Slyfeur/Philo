/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuytters <tuytters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 10:08:08 by tuytters          #+#    #+#             */
/*   Updated: 2021/12/01 08:40:24 by tuytters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

unsigned long	ft_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * (unsigned long) 1000) + (time.tv_usec / 1000));
}

unsigned long	ft_start(void)
{
	usleep(700000);
	return(ft_time());
}

void	ft_sleep(unsigned long long time, t_env *env)
{
	unsigned long long start;
	start = ft_time();
	while (!env->die)
	{
		if(ft_time() - start >= time)
			break;
		usleep(env->nb_philo);
	}
}

size_t	ft_strlen(const char *s)
{
	size_t	size;

	size = 0;
	while (*s++ != '\0')
		size++;
	return (size);
}

size_t	ft_digilen(int position)
{
	if (position > 0 && position < 10)
		return (1);
	else if (position > 9 && position < 100)
		return (2);
	else if (position > 99 && position < 1000)
		return (3);
	else if (position > 999 && position < 10000)
		return (4);
	return (0);
}
