/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_e_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 14:22:13 by gneto-co          #+#    #+#             */
/*   Updated: 2024/04/08 18:03:02 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int fat_philo_check(t_global_data *global_d, t_data **data)
{
	int	fat_philo;
	int i;
	int r;
	
	r = 0;
	fat_philo = 0;
	i = 0;
	pthread_mutex_lock(&(global_d->write_mutex));
	while (i < global_d->philo_amount)
	{
		// if ()
		if ((global_d->meals_to_get_fat)
			&& ((*data)[i].meals_eaten >= global_d->meals_to_get_fat))
			fat_philo++;
		i++;
	}
	if (fat_philo == global_d->philo_amount)
	{
		pthread_mutex_lock(&(global_d->dead_mutex));
		global_d->stop_signal = 1;
		pthread_mutex_unlock(&(global_d->dead_mutex));
		r = 1;
	}
	pthread_mutex_unlock(&(global_d->write_mutex));
	return r;
}

static int	action(t_global_data *global_d, t_data **data)
{
	int	i;

	if (stop_check(global_d))
		return (1);
	i = 0;
	(void)i;
	
	while (i < global_d->philo_amount)
	{
		if (((*data)[i].left == (*data)[i].right) || ((int)ft_get_time()
				- (*data)[i].time_of_last_meal >= global_d->time_to_die))
		{			
			// ft_print_msg(data[i], 'd');
			break;
		}
		i++;
	}
	if (stop_check(global_d))
		return (1);
	if(fat_philo_check(global_d, data))
		return (1);
	return (0);
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
	// ft_wait_for(data[0], ft_get_time(), 2000);
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
