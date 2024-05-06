/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 11:33:38 by gneto-co          #+#    #+#             */
/*   Updated: 2024/05/06 11:35:29 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	action(t_data *data, t_global_data *global_d)
{
	if (data->left == data->right)
		return (1);
	if (data->state == 't' && !stop_check(global_d))
	{
		if (data->id % 2 == 0)
			thinking_even(data, global_d);
		else
			thinking_odd(data, global_d);
	}
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

	data = (t_data *)original_data;
	global_d = data->global_d;
	ft_wait_for_all(global_d);
	pthread_mutex_lock(&(global_d->last_meal));
	data->time_of_last_meal = global_d->start_time;
	pthread_mutex_unlock(&(global_d->last_meal));
	if (data->id % 2)
		ft_wait_for(global_d, ft_get_time(), global_d->time_to_eat);
	if (!global_d->philo_amount % 2 && data->id == global_d->philo_amount)
		ft_wait_for(global_d, ft_get_time(), global_d->time_to_eat);
	while (1)
	{
		usleep(DELAY);
		if (action(data, global_d))
			break ;
	}
	pthread_exit(NULL);
}
