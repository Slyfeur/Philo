/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuytters <tuytters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:42:41 by tuytters          #+#    #+#             */
/*   Updated: 2021/12/02 15:10:39 by tuytters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_isdigit(int c)
{
	if (c < '0' || c > '9')
		return (0);
	return (1);
}

long long	ft_atoi(const char *nptr)
{
	int					signe;
	unsigned long long	valeur;
	int					i;

	signe = 1;
	valeur = 0;
	i = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			signe = signe * -1;
		nptr++;
	}
	while (ft_isdigit(*nptr))
	{
		valeur = valeur * 10 + (*nptr++ - '0');
		i++;
	}
	if (signe == -1 && (i >= 19 || valeur > (1ull << 63) - 1))
		return (0);
	if (signe == 1 && (i >= 19 || valeur > (1ull << 63) - 1))
		return (-1);
	return (signe * valeur);
}
