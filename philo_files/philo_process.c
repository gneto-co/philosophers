/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 11:33:38 by gneto-co          #+#    #+#             */
/*   Updated: 2024/04/10 15:19:48 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	action(t_data *data, t_global_data *global_d)
{
	if (data->state == 't')
		thinking(data, global_d);
	if (data->state == 'e')
		eating(data, global_d);
	if (data->state == 's')
		sleeping(data, global_d);
	return (stop_check(global_d));
}

void	*philo_process(void *original_data)
{
	t_data			*data;
	t_global_data	*global_d;

	// declarations
	data = (t_data *)original_data;
	global_d = data->global_d;
	// wait for all and set last meal to start time
	ft_wait_for_all(global_d);
	data->time_of_last_meal = global_d->start_time;
	// if is even wait a little
	if (data->id % 2)
		usleep(500);
	// loop until break
	while (1)
	{
		usleep(10);
		if (action(data, global_d))
			break ;
	}
	// end process
	pthread_exit(NULL);
}
