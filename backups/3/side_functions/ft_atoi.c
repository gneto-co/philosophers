/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:11:06 by gneto-co          #+#    #+#             */
/*   Updated: 2024/03/26 12:56:38 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "side.h"

int	ft_atoi(const char *nptr)
{
	int long	nbr;
	int			sinal;

	nbr = 0;
	sinal = 1;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sinal = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		nbr *= 10;
		nbr += *nptr - '0';
		nptr++;
	}
	if (nbr * sinal > INT_MAX || nbr * sinal < INT_MIN)
		nbr = 0;
	if (nbr)
		nbr *= sinal;
	return (nbr);
}
