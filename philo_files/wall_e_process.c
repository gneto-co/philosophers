/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_e_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 14:22:13 by gneto-co          #+#    #+#             */
/*   Updated: 2024/04/05 13:12:27 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	action(t_global_data *global_d, t_data **data)
{
	int	fat_philo;
	int	r;
	int	i;

	fat_philo = 0;
	r = 0;
	i = 0;
	if (stop_check(global_d))
		return (1);
	pthread_mutex_lock(&(global_d->write_mutex));
	while (i < global_d->philo_amount)
	{
		if ((global_d->meals_to_get_fat)
			&& ((*data)[i].meals_eaten >= global_d->meals_to_get_fat))
		{
			fat_philo++;
		}
		i++;
	}
	if (fat_philo == global_d->philo_amount)
	{
		global_d->stop_signal = 1;
	}
	pthread_mutex_unlock(&(global_d->write_mutex));
	return (r);
}

void	*wall_e_process(void *original_data)
{
	t_wall_e_data	*wall_e_data;
	t_global_data	*global_d;
	t_data			**data;

	wall_e_data = (t_wall_e_data *)original_data;
	global_d = wall_e_data->global_d;
	data = wall_e_data->data;
	(void)data;
	pthread_mutex_lock(&(global_d->run_mutex));
	pthread_mutex_unlock(&(global_d->run_mutex));
	while (1)
	{
		usleep(10);
		if (action(global_d, data))
			break ;
		(void)action;
	}
	pthread_exit(NULL);
}
