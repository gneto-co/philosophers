/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 10:44:54 by gneto-co          #+#    #+#             */
/*   Updated: 2024/04/06 10:44:55 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

// 0 - normal
// 1 - red
// 2 - green
// 3 - yellow
// 4 - blue
// 5 - magenta
// 6 - cyan
// 7 - white
// 8 - orange
void	ft_color(int nb)
{
	if (nb == 0)
		write(1, &"\033[0m", 4);
	else if (nb == 1)
		write(1, &"\033[0;31m", 7);
	else if (nb == 2)
		write(1, &"\033[0;32m", 7);
	else if (nb == 3)
		write(1, &"\033[0;33m", 7);
	else if (nb == 4)
		write(1, &"\033[0;34m", 7);
	else if (nb == 5)
		write(1, &"\033[0;35m", 7);
	else if (nb == 6)
		write(1, &"\033[0;36m", 7);
	else if (nb == 7)
		write(1, &"\033[0;37m", 7);
	else if (nb == 8)
		write(1, &"\033[31m\033[33m", 10);
}
