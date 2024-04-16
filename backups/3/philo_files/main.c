/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 11:33:36 by gneto-co          #+#    #+#             */
/*   Updated: 2024/04/12 16:07:18 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void main_free_free_data(t_global_data *global_d, t_data **data, pthread_t **threads)
{
	int i;
	
	// there is a error
	// destroy all mutex created
	pthread_mutex_destroy(&(global_d->write_mutex));
	pthread_mutex_destroy(&(global_d->last_meal));
	pthread_mutex_destroy(&(global_d->stop_mutex));
	pthread_mutex_destroy(&(global_d->run1_mutex));
	i = 0;
	while (i<global_d->philo_amount)
		pthread_mutex_destroy(&(global_d->forks_mutex[i++]));
	// free data
	free(global_d->forks_mutex);
	free(*data);
	free(*threads);
}

static void	main_split_1(t_data **data, t_global_data *global_d,
		pthread_t **threads)
{
	t_wall_e_data	wall_e_data;
	pthread_t		wall_e_thread;
	int				i;

	// create wall-e
	wall_e_data.global_d = global_d;
	wall_e_data.data = data;
	pthread_create(&wall_e_thread, NULL, wall_e_process,
		(void *)&(wall_e_data));
	// start the timer
	global_d->start_time = ft_get_time();
	// unlock the wait_for_all
	pthread_mutex_unlock(&(global_d->run1_mutex));
	i = 0;
	while (i < global_d->philo_amount)
		pthread_join((*threads)[i++], NULL);
	pthread_join(wall_e_thread, NULL);
}

int	main(int ac, char **av)
{
	t_global_data	global_d;
	t_data			*data;
	pthread_t		*threads;
	
	//error management
	if (ac != 5 && ac != 6)
		return (ft_error(1));
	if (global_declarations(&global_d, ac, av))
		return (1);
	// declarations and allocations
	data_allocation(&data, &global_d, &threads);
	mutex_declarations(&global_d);
	//lock the wait for all
	pthread_mutex_lock(&(global_d.run1_mutex));
	// do the real stuff
	create_philo(&data, &global_d, &threads);
	main_split_1(&data, &global_d, &threads);
	main_free_free_data(&global_d, &data, &threads);
	(void)main_free_free_data;
	return (0);
}
