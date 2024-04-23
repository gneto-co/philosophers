/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 09:48:14 by gneto-co          #+#    #+#             */
/*   Updated: 2024/04/22 18:59:00 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* TIME FUNCTIONS */
/*
	-summary-
	they are the functions how deal with time

	-funtions-
	ft_get_time()
	ft_wait_for()
*/

// it returns the actual time in miliseconds
unsigned long	ft_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * (unsigned long)1000) + (time.tv_usec / 1000));
}

// that function wait a certain amount of time
// if stop_signal is on it stops
void	ft_wait_for(t_global_data *global_d, unsigned long start_time,
		unsigned long wait_time)
{
	while ((ft_get_time() < start_time + wait_time))
	{
		if (stop_check(global_d))
			break ;
		usleep(DELAY);
	}
}
