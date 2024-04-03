/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 12:18:25 by gneto-co          #+#    #+#             */
/*   Updated: 2024/04/02 11:37:37 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

void	ft_put_str(char *str, int *len)
{
	if (!str)
		*len += write(1, "(null)", 6);
	while (*str)
		*len += write(1, str++, 1);
}

void	ft_put_number(long long int nb, int base, int *len)
{
	char	*hexa;

	hexa = "0123456789abcdef";
	if (nb < 0)
	{
		nb *= -1;
		write(1, &"-", 1);
	}
	if (nb >= base)
		ft_put_number((nb / base), base, len);
	*len += write(1, &(hexa[nb % base]), 1);
}

int	ft_printf(const char *str, ...)
{
	va_list	ptr;
	int		len;

	len = 0;
	va_start(ptr, str);
	while (*str)
	{
		if ((*str == '%') && *(str + 1))
		{
			str++;
			if (*str == 's')
				ft_put_str(va_arg(ptr, char *), &len);
			else if (*str == 'd')
				ft_put_number(va_arg(ptr, int), 10, &len);
			else if (*str == 'x')
				ft_put_number(va_arg(ptr, unsigned int), 16, &len);
		}
		else
			len += write(1, str, 1);
		str++;
	}
	return (len);
}
