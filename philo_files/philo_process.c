/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 11:33:38 by gneto-co          #+#    #+#             */
/*   Updated: 2024/04/16 10:21:52 by gneto-co         ###   ########.fr       */
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
		ft_wait_for(data, ft_get_time(), global_d->time_to_eat /*- global_d->philo_amount */);
	// loop until break //
	while (1)
	{
		usleep(DELAY);
		if (action(data, global_d))
			break ;
	}
	// end process //
	pthread_exit(NULL);
}
