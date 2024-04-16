/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:11:06 by gneto-co          #+#    #+#             */
/*   Updated: 2024/04/16 11:23:42 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "side.h"

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	ft_isnumber(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i++]))
			return (0);
	}
	return (1);
}

static void	divide(int *nbr, int *signal)
{
	*nbr = 0;
	*signal = 1;
}

int	ft_atoi(const char *nptr)
{
	int long	nbr;
	int			signal;

	if (!ft_isnumber(nptr))
		return (0);
	divide(&nbr, &signal);
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			signal = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		nbr *= 10;
		nbr += *nptr - '0';
		nptr++;
	}
	if (nbr * signal > INT_MAX || nbr * signal < INT_MIN)
		nbr = 0;
	if (nbr)
		nbr *= signal;
	return (nbr);
}
