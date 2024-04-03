/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_e_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 14:22:13 by gneto-co          #+#    #+#             */
/*   Updated: 2024/04/03 12:32:59 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int action(t_global_data *global_d ,t_data **data)
{
	int	fat_philo;
	int r;
	int i;
	
	fat_philo = 0;
	r = 0;
	i = 0;
	
	if(stop_check(global_d))
		return 1;

	pthread_mutex_lock(&(global_d->write_mutex));

	// check if someone died
	// or if everyone ate all spaghetti
	while (i < global_d->philo_amount)
	{
		if ((global_d->meals_to_get_fat) && ((*data)[i].meals_eaten >= global_d->meals_to_get_fat))
		{
			fat_philo++;
		}
		i++;
	}
	// if everyone ate all spaghetti
	if (fat_philo == global_d->philo_amount)
	{
		global_d->stop_signal = 1;
		ft_color(1);
		ft_printf("\n\nWall-e call an ambulance, everyone ate too much spaghetti");
		ft_color(0);
	}
	
	pthread_mutex_unlock(&(global_d->write_mutex));

	return r;
}

void *wall_e_process(void *original_data)
{
	t_wall_e_data	*wall_e_data = (t_wall_e_data *)original_data;
	t_global_data	*global_d = wall_e_data->global_d;
	t_data			**data = wall_e_data->data;

	(void)data;

    // wait for other processes to start
	pthread_mutex_lock(&(global_d->run_mutex));
	pthread_mutex_unlock(&(global_d->run_mutex));

    // loop
    while (1)
    {
        usleep(10);
		if (action(global_d, data))
			break;
		(void) action;
    }
	
	pthread_exit(NULL);
}
