/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuytters <tuytters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:42:41 by tuytters          #+#    #+#             */
/*   Updated: 2021/12/01 08:20:12 by tuytters         ###   ########.fr       */
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

static int	ft_lennb(long long n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		i++;
		n = -n;
	}
	while (n)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char			*valeur;
	int				len;
	long long int	nb;

	nb = n;
	len = ft_lennb(nb);
	valeur = malloc(sizeof(char) * len + 1);
	if (!valeur)
		return (NULL);
	if (nb < 0)
	{
		valeur[0] = '-';
		nb = -nb;
	}
	else if (nb == 0)
		valeur[0] = '0';
	valeur[len--] = '\0';
	while (nb)
	{
		valeur[len--] = nb % 10 + '0';
		nb /= 10;
	}
	return (valeur);
}
